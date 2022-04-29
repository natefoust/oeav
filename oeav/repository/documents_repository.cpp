#pragma once

#include "documents_repository.h"

#include <boost/make_shared.hpp>
#include <pqxx/pqxx>

#include "../shared/iconnection.h"
#include "../shared/instance_factory.h"

#include "../domain/analytical_type.h"
#include "../domain/analytical_accounting_code.h"
#include "../domain/account.h"
#include "../domain/oeav_primary_document.h"
#include "../domain/typical_operation.h"
#include "../domain/document.h"
#include "../services/icardfiles_service.h"

using namespace oeav::domain;
using namespace pqxx;

boost::shared_ptr<DocumentList> DocumentsRepository::getDocuments() const
{
	Document doc;
	boost::shared_ptr<DocumentList> docList = boost::make_shared<DocumentList>();

	std::string sql{ "select * from oeav_documents order by oeav_d_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	for (auto row : *result)
	{
		doc.setID(row[0].as<int>());
		doc.setSum(row[3].as<float>());
		std::string date = row[4].c_str();
		if (date != "infinity")
			doc.setDate(CTime(std::stoi(date.substr(0, 4)), std::stoi(date.substr(5, 7)), std::stoi(date.substr(8, 10)), 0, 0, 0));
		doc.setCurrentOperation(row[2].as<int>());

		if (!row[1].is_null())
		{
			doc.setPrimaryDocument(*InstanceFactory<service::ICardfilesService>::getInstance()->getPrimaryDocument(row[1].as<int>()));
			if (doc.getPrimaryDocument().getID() != 0)
			{
				doc.setTypicalOperations(*InstanceFactory<service::ICardfilesService>::getInstance()->getTypicalOperationsByDocId(doc.getPrimaryDocument().getID()));

				if (doc.getPrimaryDocument().getAnalyt1().getID() != 0)
					doc.setAnalytCode1(*InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCode(row[5].as<int>()));
				else
					doc.setAnalytCode1(AnalyticalAccountingCode());

				if (doc.getPrimaryDocument().getAnalyt2().getID() != 0)
					doc.setAnalytCode2(*InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCode(row[6].as<int>()));
				else
					doc.setAnalytCode2(AnalyticalAccountingCode());

				if (doc.getPrimaryDocument().getAnalyt3().getID() != 0)
					doc.setAnalytCode3(*InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCode(row[7].as<int>()));
				else
					doc.setAnalytCode3(AnalyticalAccountingCode());
			}
			else
				doc.setTypicalOperations(TypicalOperationList());
		}
		else
		{
			doc.setPrimaryDocument(PrimaryDocument());
			doc.setTypicalOperations(TypicalOperationList());
		}
		
		docList->emplace_back(doc);
	}

	return docList;
}

void DocumentsRepository::updateDocument(int id, int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const
{
	std::string sql{ "update oeav_documents set oeav_d_sum = '" + sum + "', oeav_d_date = '" + date + "'" };
	if (doc && doc != 0)
		sql += " , oeav_d_doc = '" + std::to_string(doc) + "'";
	if (oper && oper != 0)
		sql += " , oeav_d_operation = '" + std::to_string(oper) + "'";
	if (kau1 && kau1 != 0)
		sql += " , oeav_d_kau1 = '" + std::to_string(kau1) + "'";
	if (kau2 && kau2 != 0)
		sql += " , oeav_d_kau2 = '" + std::to_string(kau2) + "'";
	if (kau3 && kau3 != 0)
		sql += " , oeav_d_kau3 = '" + std::to_string(kau3) + "'";
	sql += " where oeav_d_id = '" + std::to_string(id) + "'";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void DocumentsRepository::deleteDocument(int id) const
{
	std::string sql{ "delete from oeav_documents where oeav_d_id = '" + std::to_string(id) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void DocumentsRepository::addDocument(int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const
{
	std::string summ = sum;
	if (summ.empty())
		summ = "0";

	if (date.empty())
		date = "infinity";

	std::string sql{ "insert into oeav_documents(oeav_d_doc, oeav_d_operation, oeav_d_sum, oeav_d_date, oeav_d_kau1, oeav_d_kau2, oeav_d_kau3)"
		" values('" + std::to_string(doc) + "', '" + std::to_string(oper) + "', '" + summ + "', '" + date + "', '" + std::to_string(kau1) +
		 "', '" + std::to_string(kau2) + "', '" + std::to_string(kau3) + "')" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

