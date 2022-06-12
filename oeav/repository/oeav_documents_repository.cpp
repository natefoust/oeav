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

	std::string sql{ "select oeav_pd_id, oeav_pd_dokk, coalesce(oeav_pd_dokd, 'infinity') as oeav_pd_dokd,"
					" coalesce(oeav_pd_ak1, 0) as oeav_pd_ak1, coalesce(oeav_pd_ak2, 0) as oeav_pd_ak2,"
					" coalesce(oeav_pd_ak3, 0) as oeav_pd_ak3,  coalesce(oeav_pd_rub, 0) as oeav_pd_rub,"
					" coalesce(oeav_pd_to, 0) as oeav_pd_to"
					" from oeav_pd order by oeav_pd_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	for (auto row : *result)
	{
		doc.setID(row.at("oeav_pd_id").as<int>());
		doc.setSum(row.at("oeav_pd_rub").as<int>());
		std::string date = row.at("oeav_pd_dokd").c_str();
		if (date != "infinity")
		{
			doc.setDate(CTime(std::stoi(date.substr(0, 4)), std::stoi(date.substr(5, 7)), std::stoi(date.substr(8, 10)), 0, 0, 0));
			std::stringstream ss;
			ss << doc.getDate().GetYear();
		}
		doc.setCurrentOperation(row.at("oeav_pd_to").as<int>());

		if (!row.at("oeav_pd_dokk").is_null())
		{
			doc.setPrimaryDocument(*InstanceFactory<service::ICardfilesService>::getInstance()->getPrimaryDocument(row.at("oeav_pd_dokk").as<int>()));
			if (doc.getPrimaryDocument().getID() != 0)
			{
				doc.setTypicalOperations(*InstanceFactory<service::ICardfilesService>::getInstance()->getTypicalOperationsByDocId(doc.getPrimaryDocument().getID()));

				if (doc.getPrimaryDocument().getAnalyt1().getID() != 0)
					doc.setAnalytCode1(*InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCode(row.at("oeav_pd_ak1").as<int>()));
				else
					doc.setAnalytCode1(AnalyticalAccountingCode());

				if (doc.getPrimaryDocument().getAnalyt2().getID() != 0)
					doc.setAnalytCode2(*InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCode(row.at("oeav_pd_ak2").as<int>()));
				else
					doc.setAnalytCode2(AnalyticalAccountingCode());

				if (doc.getPrimaryDocument().getAnalyt3().getID() != 0)
					doc.setAnalytCode3(*InstanceFactory<service::ICardfilesService>::getInstance()->getAnalyticalAccountingCode(row.at("oeav_pd_ak3").as<int>()));
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
	std::string sql{ "update oeav_pd set oeav_pd_rub = '" + sum + "', oeav_pd_dokd = '" + date + "'" };
	if (doc && doc != 0)
		sql += " , oeav_pd_dokk = '" + std::to_string(doc) + "'";
	if (oper && oper != 0)
		sql += " , oeav_pd_to = '" + std::to_string(oper) + "'";
	if (kau1 && kau1 != 0)
		sql += " , oeav_pd_ak1 = '" + std::to_string(kau1) + "'";
	if (kau2 && kau2 != 0)
		sql += " , oeav_pd_ak2 = '" + std::to_string(kau2) + "'";
	if (kau3 && kau3 != 0)
		sql += " , oeav_pd_ak3 = '" + std::to_string(kau3) + "'";
	sql += " where oeav_pd_id = '" + std::to_string(id) + "'";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void DocumentsRepository::deleteDocument(int id) const
{
	std::string sql{ "delete from oeav_pd where oeav_pd_id = '" + std::to_string(id) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void DocumentsRepository::addDocument(int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const
{
	std::string summ = sum;
	if (summ.empty())
		summ = "0";

	if (date.empty())
		date = "infinity";

	std::string sql{ "insert into oeav_pd(oeav_pd_dokk, oeav_pd_to, oeav_pd_rub, oeav_pd_dokd, oeav_pd_ak1, oeav_pd_ak2, oeav_pd_ak3)"
		" values('" + std::to_string(doc) + "', '" + std::to_string(oper) + "', '" + summ + "', '" + date + "', '" + std::to_string(kau1) +
		 "', '" + std::to_string(kau2) + "', '" + std::to_string(kau3) + "')" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void DocumentsRepository::registerDocument(const std::string & date, const std::string & docName, const std::string & docCode,
	const std::string & docDate, const std::string & operation, const std::string & debetCode, const std::string & debetName,
	const std::string & creditCode, const std::string & creditName, const std::string & sum, const std::string & debetT,
	const std::string & creditT) const 
{
	std::string sql{ "insert into oeav_rj(oeav_rj_data, oeav_rj_dokn, oeav_rj_dokk, oeav_rj_dokd, "
		" oeav_rj_to, oeav_rj_db, oeav_rj_dbn, oeav_rj_kr, oeav_rj_krn, "
		" oeav_rj_rub) values('" + date + "', '" + docName + "', '" + docCode + "', '" + docDate + "', '"
		+ operation + "', '" + debetCode + "', '" + debetName + "', '" + creditCode + "', '" + creditName + "', '" + sum + "')" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

boost::shared_ptr<RegBookItemList> DocumentsRepository::getRegisteredDocuments() const
{
	std::string sql{ "select oeav_rj_id, coalesce(oeav_rj_data, 'infinity') as oeav_rj_data, coalesce(oeav_rj_dokk, '') as oeav_rj_dokk,"
				" coalesce(oeav_rj_dokn, '0') as oeav_rj_dokn, coalesce(oeav_rj_dokd, 'infinity') as oeav_rj_dokd,"
				" coalesce(oeav_rj_to, '') as oeav_rj_to, coalesce(oeav_rj_db, 0) as oeav_rj_db, coalesce(oeav_rj_dbn, '') as oeav_rj_dbn,"
				" coalesce(oeav_rj_kr, 0) as oeav_rj_kr, coalesce(oeav_rj_krn, '') as oeav_rj_krn, coalesce(oeav_rj_rub, 0) as oeav_rj_rub"
				" from oeav_rj order by oeav_rj_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<RegBookItemList> _regBookList = boost::make_shared<RegBookItemList>();
	
	std::string date, docDate;
	for (auto row : *result)
	{
		date = row.at("oeav_rj_data").c_str(); 
		docDate = row.at("oeav_rj_dokd").c_str();

		if (date == "infinity")
			date = "";
		if (docDate == "infinity")
			docDate = "";

		_regBookList->emplace_back(RegBookItem(row.at("oeav_rj_id").as<int>(), date, row.at("oeav_rj_dokn").c_str(), row.at("oeav_rj_dokk").c_str(), 
			docDate, row.at("oeav_rj_to").c_str(), row.at("oeav_rj_db").c_str(), row.at("oeav_rj_dbn").c_str(), row.at("oeav_rj_kr").c_str(), 
			row.at("oeav_rj_krn").c_str(), row.at("oeav_rj_rub").c_str(), "", ""));
	}

	return _regBookList;
}

int DocumentsRepository::generateAccountsBook() const
{
	InstanceFactory<IConnection>::getInstance()->execute("truncate table oeav_ks");

	boost::shared_ptr<RegBookItemList> regBookList = getRegisteredDocuments();

	int i = 0;
	for (auto item : *regBookList)
	{
		InstanceFactory<IConnection>::getInstance()->execute("insert into oeav_ks(oeav_ks_data, oeav_ks_dokk, oeav_ks_dokn, oeav_ks_dokd,"
			" oeav_ks_to, oeav_ks_s, oeav_ks_sn, oeav_ks_ks, oeav_ks_ksn,"
			" oeav_ks_db, oeav_ks_kr) values('" + (item.getDate().empty() ? "infinity" : item.getDate()) + "', '" + item.getDocCode() +"', '" + item.getDocName() + "', '" + (item.getDocDate().empty() ? "infinity" : item.getDocDate()) + "', '"
			+ item.getOperation() + "', '" + item.getDebetCode() + "', '" + item.getDebetName() + "', '" + item.getCreditCode() + "', '"
			+ item.getCreditName() + "', '" + item.getSum() + "', '" + "0" + "')");

		InstanceFactory<IConnection>::getInstance()->execute("insert into oeav_ks(oeav_ks_data, oeav_ks_dokk, oeav_ks_dokn, oeav_ks_dokd,"
			" oeav_ks_to, oeav_ks_s, oeav_ks_sn, oeav_ks_ks, oeav_ks_ksn,"
			" oeav_ks_db, oeav_ks_kr) values('" + (item.getDate().empty() ? "infinity" : item.getDate()) + "', '" + item.getDocCode() + "', '" + item.getDocName() + "', '" + (item.getDocDate().empty() ? "infinity" : item.getDocDate()) + "', '"
			+ item.getOperation() + "', '" + item.getCreditCode() + "', '" + item.getCreditName() + "', '" + item.getDebetCode() + "', '"
			+ item.getDebetName() + "', '" + "0" + "', '" + item.getSum() + "')");
		i++;
	}

	return i;
}

boost::shared_ptr<AccBookItemList> DocumentsRepository::getAccBookList() const
{
	std::string sql{ "select * from oeav_ks" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AccBookItemList> accBookList = boost::make_shared<AccBookItemList>();

	std::string date, docDate;
	for (auto row : *result)
	{
		date = row.at("oeav_ks_data").c_str();
		docDate = row.at("oeav_ks_dokd").c_str();

		if (date == "infinity")
			date = "";
		if (docDate == "infinity")
			docDate = "";

		accBookList->emplace_back(AccBookItem(row.at("oeav_ks_id").as<int>(), date, row.at("oeav_ks_dokn").c_str(), row.at("oeav_ks_dokk").c_str(),
			docDate, row.at("oeav_ks_to").c_str(), row.at("oeav_ks_s").c_str(), row.at("oeav_ks_sn").c_str(), row.at("oeav_ks_ks").c_str(),
			row.at("oeav_ks_ksn").c_str(), row.at("oeav_ks_db").c_str(), row.at("oeav_ks_kr").c_str()));
	}

	return accBookList;
}

const std::string DocumentsRepository::getBO() const
{
	std::string resultStr =
		"=Огиевич Е.А.=              Балансовая ведомость              =oea_krv=\r\n"
		"    по счёту " + getTargetAccCode() + "          период с " + getDateFrom() + " по " + getDateTo() + "           \r\n"
		"-----------------------------------------------------------------------\r\n"
		"    Счёт                             Корр.счёт                              Дебет\r\n"
		"-----------------------------------------------------------------------\r\n";

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute("select * from oeav_ks where oeav_ks_db != 0 and oeav_ks_s = '" + getTargetAccCode() + "' and oeav_ks_data >= '" +
			getDateFrom() + "' and oeav_ks_data <= '" + getDateTo() + "'");

	int debet = 0;
	for (auto row : *result)
	{
		resultStr += "      " + std::to_string(row.at("oeav_ks_s").as<int>()) + "                                    " + std::to_string(row.at("oeav_ks_ks").as<int>()) + 
			"                                        " + std::to_string(row.at("oeav_ks_db").as<int>()) + "\r\n";

		debet += row.at("oeav_ks_db").as<int>();
	}

	resultStr += "												                                       Итого по счёту: " + std::to_string(debet);

	return resultStr;
}

const std::string DocumentsRepository::getJO() const
{
	std::string resultStr =
		"=Огиевич Е.А.=              Журнал-ордер                      =oea_krv=\r\n"
		"    по счёту " + getTargetAccCode() + "          период с " + getDateFrom() + " по " + getDateTo() + "           \r\n"
		"-----------------------------------------------------------------------\r\n"
		"    Счёт                             Корр.счёт                              Кредит\r\n"
		"-----------------------------------------------------------------------\r\n";

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute("select * from oeav_ks where oeav_ks_kr != 0 and oeav_ks_s = '" + getTargetAccCode() + "' and oeav_ks_data >= '" +
			getDateFrom() + "' and oeav_ks_data <= '" + getDateTo() +  "'");

	int credit = 0;
	for (auto row : *result)
	{
		resultStr += "      " + std::to_string(row.at("oeav_ks_s").as<int>()) + "                                    " + std::to_string(row.at("oeav_ks_ks").as<int>()) +
			"                                        " + std::to_string(row.at("oeav_ks_kr").as<int>()) + "\r\n";
		
		credit += row.at("oeav_ks_kr").as<int>();
	}

	resultStr += "												                                       Итого по счёту: " + std::to_string(credit);

	return resultStr;
}

void DocumentsRepository::updateDateFrom(const std::string &dateFrom) const
{
	InstanceFactory<IConnection>::getInstance()->execute("update oeav_nst set oeav_nst_dats = '" + dateFrom + "'");
}

void DocumentsRepository::updateDateTo(const std::string &dateTo) const
{
	InstanceFactory<IConnection>::getInstance()->execute("update oeav_nst set oeav_nst_datd = '" + dateTo + "'");
}

void DocumentsRepository::updateTargetAccount(const std::string &code, const std::string &name) const
{
	InstanceFactory<IConnection>::getInstance()->execute("update oeav_nst set oeav_nst_s = '" + code + "', oeav_nst_sn = '" + name + "'");
}

void DocumentsRepository::updateCompanyName(const std::string &name) const
{
	InstanceFactory<IConnection>::getInstance()->execute("update oeav_nst set oeav_nst_firm = '" + name + "'");
}

void DocumentsRepository::updateCurrentDate(const std::string &date) const
{
	InstanceFactory<IConnection>::getInstance()->execute("update oeav_nst set oeav_nst_datt = '" + date + "'");
}

std::string DocumentsRepository::getDateFrom() const
{
	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute("select coalesce(oeav_nst_dats, '1970-01-01') as oeav_nst_dats from oeav_nst");
	auto row = result->at(0);
	
	return row.at("oeav_nst_dats").c_str();
}

std::string DocumentsRepository::getDateTo() const
{
	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute("select coalesce(oeav_nst_datd, '1970-01-01') as oeav_nst_datd from oeav_nst");
	auto row = result->at(0);

	return row.at("oeav_nst_datd").c_str();
}

std::string DocumentsRepository::getTargetAccount() const
{
	boost::shared_ptr<result> result1 =
		InstanceFactory<IConnection>::getInstance()->execute("select coalesce(oeav_nst_s, 0) as oeav_nst_s, coalesce(oeav_nst_sn, '') as oeav_nst_sn  from oeav_nst");

	auto row = result1->at(0);

	std::string acc = std::string(row.at("oeav_nst_s").c_str()) + " - " + std::string(row.at("oeav_nst_sn").c_str());

	return acc;
}

std::string DocumentsRepository::getCompanyName() const
{
	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute("select coalesce(oeav_nst_firm, '') as oeav_nst_firm from oeav_nst");
	auto row = result->at(0);

	return row.at("oeav_nst_firm").c_str();
}

std::string DocumentsRepository::getCurrentDate() const
{
	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute("select coalesce(oeav_nst_datt, '1970-01-01') as oeav_nst_datt from oeav_nst");
	auto row = result->at(0);

	return row.at("oeav_nst_datt").c_str();
}

std::string DocumentsRepository::getTargetAccCode() const
{
	boost::shared_ptr<result> result1 =
		InstanceFactory<IConnection>::getInstance()->execute("select coalesce(oeav_nst_s, 0) as oeav_nst_s from oeav_nst");

	auto row = result1->at(0);

	return row.at("oeav_nst_s").c_str();
}

const std::string DocumentsRepository::getKS() const
{
	std::string resultStr =
		"=Огиевич Е.А.=                           Книга счетов                       =oea_krx=\r\n"
		"-------------------------------------------------------------------------------------\r\n"
		" Дата          Документ     Операция          Счёт      К.Счёт       Дебет     Кредит\r\n"
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
		"=Огиевич Е.А.=                   Оборотно-сальдовая ведомость                =oea_kro=\r\n"
		"    по счёту " + getTargetAccCode() + "          период с " + getDateFrom() + " по " + getDateTo() + "           \r\n"
		"                                   входящее и исходящее сальдо не считать            \r\n"
		"-------------------------------------------------------------------------------------\r\n"
		" Дата             Документ       Операция          Счёт      К.Счёт         Оборот     \r\n"
		"                                                                                             дб      кр    \r\n"
		"-------------------------------------------------------------------------------------\r\n";

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute("select * from oeav_ks where oeav_ks_s = '" + getTargetAccCode() + "' and oeav_ks_data >= '" +
			getDateFrom() + "' and oeav_ks_data <= '" + getDateTo() + "'");

	const auto f = [&](std::string str, int size) {

		std::string s{};
		for (int i = 0; i < size - str.length(); i++)
			s.append(" ");

		return s;
	};

	int countDb = 0, countKr = 0;
	for (auto &row : *result)
	{
		resultStr += std::string(row.at("oeav_ks_data").c_str()) + f(row.at("oeav_ks_data").c_str(), 15) + std::string(row.at("oeav_ks_dokn").c_str()) +
			f(row.at("oeav_ks_dokn").c_str(), 15) + std::string(row.at("oeav_ks_to").c_str()) + f(row.at("oeav_ks_to").c_str(), 22) + std::string(row.at("oeav_ks_s").c_str()) +
			f(row.at("oeav_ks_s").c_str(), 12) +
			std::string(row.at("oeav_ks_ks").c_str()) + f(row.at("oeav_ks_ks").c_str(), 12) + std::string(row.at("oeav_ks_db").c_str()) + f(row.at("oeav_ks_db").c_str(), 9)
			+ std::string(row.at("oeav_ks_kr").c_str()) + "\r\n";

		countDb += row.at("oeav_ks_db").as<int>();
		countKr += row.at("oeav_ks_kr").as<int>();
	}
	resultStr += f("", 69) + "Итого по счёту: " + std::to_string(countDb) + f(std::to_string(countDb), 9) + std::to_string(countKr);

	return resultStr;
}