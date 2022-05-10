#pragma once

#include "oeav_documents_repository.h"

#include <boost/make_shared.hpp>
#include <pqxx/pqxx>

#include "../shared/oeav_iconnection.h"
#include "../shared/oeav_instance_factory.h"

#include "../domain/oeav_analytical_type.h"
#include "../domain/oeav_analytical_accounting_code.h"
#include "../domain/oeav_account.h"
#include "../domain/oeav_primary_document.h"
#include "../domain/oeav_typical_operation.h"
#include "../domain/oeav_document.h"
#include "../services/oeav_icardfiles_service.h"
#include "../domain/oeav_reg_book_item.h"
#include "../domain/oeav_acc_book_item.h"

using namespace oeav::domain;
using namespace pqxx;

boost::shared_ptr<DocumentList> DocumentsRepository::getDocuments() const
{
	Document doc;
	boost::shared_ptr<DocumentList> docList = boost::make_shared<DocumentList>();

	std::string sql{ "select oeav_pid, oeav_pdok, coalesce(oeav_pdokd, 'infinity') as oeav_pdokd,"
					" coalesce(oeav_pak1, 0) as oeav_pak1, coalesce(oeav_pak2, 0) as oeav_pak2,"
					" coalesce(oeav_pak3, 0) as oeav_pak3,  coalesce(oeav_prub, 0) as oeav_prub,"
					" coalesce(oeav_pto, 0) as oeav_pto"
					" from oeav_p order by oeav_pid" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	for (auto row : *result)
	{
		doc.setID(row.at("oeav_pid").as<int>());
		doc.setSum(row.at("oeav_prub").as<int>());
		std::string date = row.at("oeav_pdokd").c_str();
		if (date != "infinity")
		{
			doc.setDate(CTime(std::stoi(date.substr(0, 4)), std::stoi(date.substr(5, 7)), std::stoi(date.substr(8, 10)), 0, 0, 0));
			std::stringstream ss;
			ss << doc.getDate().GetYear();
		}
		doc.setCurrentOperation(row.at("oeav_pto").as<int>());

		if (!row.at("oeav_pdok").is_null())
		{
			doc.setPrimaryDocument(*InstanceFactory<service::ICardfilesService>::getInstance()->getPrimaryDocument(row.at("oeav_pdok").as<int>()));
			if (doc.getPrimaryDocument().getID() != 0)
			{
				doc.setTypicalOperations(*InstanceFactory<service::ICardfilesService>::getInstance()->getTypicalOperationsByDocId(doc.getPrimaryDocument().getID()));

				if (doc.getPrimaryDocument().getAnalyt1().getID() != 0)
					doc.setAnalytCode1(*InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCode(row.at("oeav_pak1").as<int>()));
				else
					doc.setAnalytCode1(AnalyticalAccountingCode());

				if (doc.getPrimaryDocument().getAnalyt2().getID() != 0)
					doc.setAnalytCode2(*InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCode(row.at("oeav_pak2").as<int>()));
				else
					doc.setAnalytCode2(AnalyticalAccountingCode());

				if (doc.getPrimaryDocument().getAnalyt3().getID() != 0)
					doc.setAnalytCode3(*InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCode(row.at("oeav_pak3").as<int>()));
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
	std::string sql{ "update oeav_p set oeav_prub = '" + sum + "', oeav_pdokd = '" + date + "'" };
	if (doc && doc != 0)
		sql += " , oeav_pdok = '" + std::to_string(doc) + "'";
	if (oper && oper != 0)
		sql += " , oeav_pto = '" + std::to_string(oper) + "'";
	if (kau1 && kau1 != 0)
		sql += " , oeav_pak1 = '" + std::to_string(kau1) + "'";
	if (kau2 && kau2 != 0)
		sql += " , oeav_pak2 = '" + std::to_string(kau2) + "'";
	if (kau3 && kau3 != 0)
		sql += " , oeav_pak3 = '" + std::to_string(kau3) + "'";
	sql += " where oeav_pid = '" + std::to_string(id) + "'";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void DocumentsRepository::deleteDocument(int id) const
{
	std::string sql{ "delete from oeav_p where oeav_pid = '" + std::to_string(id) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void DocumentsRepository::addDocument(int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const
{
	std::string summ = sum;
	if (summ.empty())
		summ = "0";

	if (date.empty())
		date = "infinity";

	std::string sql{ "insert into oeav_p(oeav_pdok, oeav_pto, oeav_prub, oeav_pdokd, oeav_pak1, oeav_pak2, oeav_pak3)"
		" values('" + std::to_string(doc) + "', '" + std::to_string(oper) + "', '" + summ + "', '" + date + "', '" + std::to_string(kau1) +
		 "', '" + std::to_string(kau2) + "', '" + std::to_string(kau3) + "')" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void DocumentsRepository::registerDocument(const std::string & date, const std::string & docName, const std::string & docCode,
	const std::string & docDate, const std::string & operation, const std::string & debetCode, const std::string & debetName,
	const std::string & creditCode, const std::string & creditName, const std::string & sum, const std::string & debetT,
	const std::string & creditT) const 
{
	std::string sql{ "insert into oeav_j(oeav_jdata, oeav_jdokn, oeav_jdokk, oeav_jdokd, "
		" oeav_jto, oeav_jdb, oeav_jdbn, oeav_jkr, oeav_jkrn, "
		" oeav_jrub) values('" + date + "', '" + docName + "', '" + docCode + "', '" + docDate + "', '"
		+ operation + "', '" + debetCode + "', '" + debetName + "', '" + creditCode + "', '" + creditName + "', '" + sum + "')" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

boost::shared_ptr<RegBookItemList> DocumentsRepository::getRegisteredDocuments() const
{
	std::string sql{ "select oeav_jid, coalesce(oeav_jdata, 'infinity') as oeav_jdata, coalesce(oeav_jdokk, '') as oeav_jdokk,"
				" coalesce(oeav_jdokn, '0') as oeav_jdokn, coalesce(oeav_jdokd, 'infinity') as oeav_jdokd,"
				" coalesce(oeav_jto, '') as oeav_jto, coalesce(oeav_jdb, 0) as oeav_jdb, coalesce(oeav_jdbn, '') as oeav_jdbn,"
				" coalesce(oeav_jkr, 0) as oeav_jkr, coalesce(oeav_jkrn, '') as oeav_jkrn, coalesce(oeav_jrub, 0) as oeav_jrub"
				" from oeav_j order by oeav_jid" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<RegBookItemList> _regBookList = boost::make_shared<RegBookItemList>();
	
	std::string date, docDate;
	for (auto row : *result)
	{
		date = row.at("oeav_jdata").c_str(); 
		docDate = row.at("oeav_jdokd").c_str();

		if (date == "infinity")
			date = "";
		if (docDate == "infinity")
			docDate = "";

		_regBookList->emplace_back(RegBookItem(row.at("oeav_jid").as<int>(), date, row.at("oeav_jdokn").c_str(), row.at("oeav_jdokk").c_str(), 
			docDate, row.at("oeav_jto").c_str(), row.at("oeav_jdb").c_str(), row.at("oeav_jdbn").c_str(), row.at("oeav_jkr").c_str(), 
			row.at("oeav_jkrn").c_str(), row.at("oeav_jrub").c_str(), "", ""));
	}

	return _regBookList;
}

int DocumentsRepository::generateAccountsBook() const
{
	InstanceFactory<IConnection>::getInstance()->execute("truncate table oeav_k");

	boost::shared_ptr<RegBookItemList> regBookList = getRegisteredDocuments();

	int i = 0;
	for (auto item : *regBookList)
	{
		InstanceFactory<IConnection>::getInstance()->execute("insert into oeav_k(oeav_kdata, oeav_kdokk, oeav_kdokn, oeav_kdokd,"
			" oeav_kto, oeav_ks, oeav_ksn, oeav_kks, oeav_kksn,"
			" oeav_kdb, oeav_kkr) values('" + (item.getDate().empty() ? "infinity" : item.getDate()) + "', '" + item.getDocCode() +"', '" + item.getDocName() + "', '" + (item.getDocDate().empty() ? "infinity" : item.getDocDate()) + "', '"
			+ item.getOperation() + "', '" + item.getDebetCode() + "', '" + item.getDebetName() + "', '" + item.getCreditCode() + "', '"
			+ item.getCreditName() + "', '" + item.getSum() + "', '" + "0" + "')");

		InstanceFactory<IConnection>::getInstance()->execute("insert into oeav_k(oeav_kdata, oeav_kdokk, oeav_kdokn, oeav_kdokd,"
			" oeav_kto, oeav_ks, oeav_ksn, oeav_kks, oeav_kksn,"
			" oeav_kdb, oeav_kkr) values('" + (item.getDate().empty() ? "infinity" : item.getDate()) + "', '" + item.getDocCode() + "', '" + item.getDocName() + "', '" + (item.getDocDate().empty() ? "infinity" : item.getDocDate()) + "', '"
			+ item.getOperation() + "', '" + item.getCreditCode() + "', '" + item.getCreditName() + "', '" + item.getDebetCode() + "', '"
			+ item.getDebetName() + "', '" + "0" + "', '" + item.getSum() + "')");
		i++;
	}

	return i;
}

boost::shared_ptr<AccBookItemList> DocumentsRepository::getAccBookList() const
{
	std::string sql{ "select * from oeav_k" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AccBookItemList> accBookList = boost::make_shared<AccBookItemList>();

	std::string date, docDate;
	for (auto row : *result)
	{
		date = row.at("oeav_kdata").c_str();
		docDate = row.at("oeav_kdokd").c_str();

		if (date == "infinity")
			date = "";
		if (docDate == "infinity")
			docDate = "";

		accBookList->emplace_back(AccBookItem(row.at("oeav_kid").as<int>(), date, row.at("oeav_kdokn").c_str(), row.at("oeav_kdokk").c_str(),
			docDate, row.at("oeav_kto").c_str(), row.at("oeav_ks").c_str(), row.at("oeav_ksn").c_str(), row.at("oeav_kks").c_str(),
			row.at("oeav_kksn").c_str(), row.at("oeav_kdb").c_str(), row.at("oeav_kkr").c_str()));
	}

	return accBookList;
}

const std::string DocumentsRepository::getBO() const
{
	std::string resultStr =
		"=������� �.�.=              ���������� ���������              =oea_krv=\r\n"
		"    �� ����� " + getTargetAccCode() + "          ������ � " + getDateFrom() + " �� " + getDateTo() + "           \r\n"
		"-----------------------------------------------------------------------\r\n"
		"    ����                             ����.����                              �����\r\n"
		"-----------------------------------------------------------------------\r\n";

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute("select * from oeav_k where oeav_kdb != 0 and oeav_ks = '" + getTargetAccCode() + "' and oeav_kdata >= '" +
			getDateFrom() + "' and oeav_kdata <= '" + getDateTo() + "'");

	int debet = 0;
	for (auto row : *result)
	{
		resultStr += "      " + std::to_string(row.at("oeav_ks").as<int>()) + "                                    " + std::to_string(row.at("oeav_kks").as<int>()) + 
			"                                        " + std::to_string(row.at("oeav_kdb").as<int>()) + "\r\n";

		debet += row.at("oeav_kdb").as<int>();
	}

	resultStr += "												                                       ����� �� �����: " + std::to_string(debet);

	return resultStr;
}

const std::string DocumentsRepository::getJO() const
{
	std::string resultStr =
		"=������� �.�.=              ������-�����                      =oea_krv=\r\n"
		"    �� ����� " + getTargetAccCode() + "          ������ � " + getDateFrom() + " �� " + getDateTo() + "           \r\n"
		"-----------------------------------------------------------------------\r\n"
		"    ����                             ����.����                              ������\r\n"
		"-----------------------------------------------------------------------\r\n";

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute("select * from oeav_k where oeav_kkr != 0 and oeav_ks = '" + getTargetAccCode() + "' and oeav_kdata >= '" +
			getDateFrom() + "' and oeav_kdata <= '" + getDateTo() +  "'");

	int credit = 0;
	for (auto row : *result)
	{
		resultStr += "      " + std::to_string(row.at("oeav_ks").as<int>()) + "                                    " + std::to_string(row.at("oeav_kks").as<int>()) +
			"                                        " + std::to_string(row.at("oeav_kkr").as<int>()) + "\r\n";
		
		credit += row.at("oeav_kkr").as<int>();
	}

	resultStr += "												                                       ����� �� �����: " + std::to_string(credit);

	return resultStr;
}

void DocumentsRepository::updateDateFrom(const std::string &dateFrom) const
{
	InstanceFactory<IConnection>::getInstance()->execute("update oeav_c set oeav_cdats = '" + dateFrom + "'");
}

void DocumentsRepository::updateDateTo(const std::string &dateTo) const
{
	InstanceFactory<IConnection>::getInstance()->execute("update oeav_c set oeav_cdatd = '" + dateTo + "'");
}

void DocumentsRepository::updateTargetAccount(const std::string &code, const std::string &name) const
{
	InstanceFactory<IConnection>::getInstance()->execute("update oeav_c set oeav_cs = '" + code + "', oeav_csn = '" + name + "'");
}

void DocumentsRepository::updateCompanyName(const std::string &name) const
{
	InstanceFactory<IConnection>::getInstance()->execute("update oeav_c set oeav_cfirm = '" + name + "'");
}

void DocumentsRepository::updateCurrentDate(const std::string &date) const
{
	InstanceFactory<IConnection>::getInstance()->execute("update oeav_c set oeav_cdatt = '" + date + "'");
}

std::string DocumentsRepository::getDateFrom() const
{
	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute("select coalesce(oeav_cdats, '1970-01-01') as oeav_cdats from oeav_c");
	auto row = result->at(0);
	
	return row.at("oeav_cdats").c_str();
}

std::string DocumentsRepository::getDateTo() const
{
	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute("select coalesce(oeav_cdatd, '1970-01-01') as oeav_cdatd from oeav_c");
	auto row = result->at(0);

	return row.at("oeav_cdatd").c_str();
}

std::string DocumentsRepository::getTargetAccount() const
{
	boost::shared_ptr<result> result1 =
		InstanceFactory<IConnection>::getInstance()->execute("select coalesce(oeav_cs, 0) as oeav_cs, coalesce(oeav_csn, '') as oeav_csn  from oeav_c");

	auto row = result1->at(0);

	std::string acc = std::string(row.at("oeav_cs").c_str()) + " - " + std::string(row.at("oeav_csn").c_str());

	return acc;
}

std::string DocumentsRepository::getCompanyName() const
{
	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute("select coalesce(oeav_cfirm, '') as oeav_cfirm from oeav_c");
	auto row = result->at(0);

	return row.at("oeav_cfirm").c_str();
}

std::string DocumentsRepository::getCurrentDate() const
{
	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute("select coalesce(oeav_cdatt, '1970-01-01') as oeav_cdatt from oeav_c");
	auto row = result->at(0);

	return row.at("oeav_cdatt").c_str();
}

std::string DocumentsRepository::getTargetAccCode() const
{
	boost::shared_ptr<result> result1 =
		InstanceFactory<IConnection>::getInstance()->execute("select coalesce(oeav_cs, 0) as oeav_cs from oeav_c");

	auto row = result1->at(0);

	return row.at("oeav_cs").c_str();
}

const std::string DocumentsRepository::getKS() const
{
	std::string resultStr =
		"=������� �.�.=                           ����� ������                       =oea_krx=\r\n"
		"-------------------------------------------------------------------------------------\r\n"
		" ����          ��������     ��������          ����      �.����       �����     ������\r\n"
		"-------------------------------------------------------------------------------------\r\n";

	boost::shared_ptr<AccBookItemList> accBookList = getAccBookList();

	const auto f = [&](std::string str, int size) {
		
		std::string s{};
		for (int i = 0; i < size - str.length(); i++)
			s.append(" ");

		return s;
	};

	for (auto &item : *accBookList)
	{
		resultStr += item.getDate() + f(item.getDate(), 15) + item.getDocCode() + f(item.getDocCode(), 13) + item.getOperation() + f(item.getOperation(), 23) + item.getAccountCode()
			+ f(item.getAccountCode(), 12) + item.getCorCode() + f(item.getCorCode(), 16) + item.getSumDb() + f(item.getSumDb(), 12) + item.getSumKr() + "\r\n";
	}

	return resultStr;
}

const std::string DocumentsRepository::getOSV() const
{
	std::string resultStr =
		"=������� �.�.=                           ����� ������                       =oea_kro=\r\n"
		"    �� ����� " + getTargetAccCode() + "          ������ � " + getDateFrom() + " �� " + getDateTo() + "           \r\n"
		"                                   �������� � ��������� ������ �� �������            \r\n"
		"-------------------------------------------------------------------------------------\r\n"
		" ����             ��������       ��������          ����      �.����         ������     \r\n"
		"                                                                                             ��      ��    \r\n"
		"-------------------------------------------------------------------------------------\r\n";

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute("select * from oeav_k where oeav_ks = '" + getTargetAccCode() + "' and oeav_kdata >= '" +
			getDateFrom() + "' and oeav_kdata <= '" + getDateTo() + "'");

	const auto f = [&](std::string str, int size) {

		std::string s{};
		for (int i = 0; i < size - str.length(); i++)
			s.append(" ");

		return s;
	};

	int countDb = 0, countKr = 0;
	for (auto &row : *result)
	{
		resultStr += std::string(row.at("oeav_kdata").c_str()) + f(row.at("oeav_kdata").c_str(), 15) + std::string(row.at("oeav_kdokn").c_str()) +
			f(row.at("oeav_kdokn").c_str(), 15) + std::string(row.at("oeav_kto").c_str()) + f(row.at("oeav_kto").c_str(), 22) + std::string(row.at("oeav_ks").c_str()) +
			f(row.at("oeav_ks").c_str(), 12) +
			std::string(row.at("oeav_kks").c_str()) + f(row.at("oeav_kks").c_str(), 12) + std::string(row.at("oeav_kdb").c_str()) + f(row.at("oeav_kdb").c_str(), 9)
			+ std::string(row.at("oeav_kkr").c_str()) + "\r\n";

		countDb += row.at("oeav_kdb").as<int>();
		countKr += row.at("oeav_kkr").as<int>();
	}
	resultStr += f("", 69) + "����� �� �����: " + std::to_string(countDb) + f(std::to_string(countDb), 9) + std::to_string(countKr);

	return resultStr;
}