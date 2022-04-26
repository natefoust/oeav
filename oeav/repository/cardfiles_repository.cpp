#pragma once

#include "cardfiles_repository.h"

#include <boost/make_shared.hpp>
#include <pqxx/pqxx>

#include "../shared/iconnection.h"
#include "../shared/instance_factory.h"

#include "../domain/analytical_type.h"
#include "../domain/analytical_accounting_code.h"
#include "../domain/account.h"
#include "../domain/oeav_primary_document.h"

using namespace oeav::domain;
using namespace pqxx;

boost::shared_ptr<AnalyticalAccountingCodeList> CardfilesRepository::getAnalyticalAccountingCodes() const
{
	std::string sql{ "SELECT * FROM OEAV_ANALYTICAL_ACCOUNTING_CODES OAAC INNER JOIN OEAV_ANALYTICAL_TYPES OAT"
		" ON OAAC.OEAV_ANALYTICAL_TYPE = OAT.OEAV_AT_ID ORDER BY oeav_id" };

	boost::shared_ptr<result> result = 
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AnalyticalAccountingCodeList> analytCodesList = boost::make_shared<AnalyticalAccountingCodeList>();

	for (auto row : *result)
		analytCodesList->emplace_back(AnalyticalAccountingCode(row[0].as<int>(), 0, AnalyticalType(row[4].as<int>(), row[5].c_str(),
			row[6].c_str()), row[3].c_str()));

	return analytCodesList;
}

void CardfilesRepository::addAnalyticalAccountingCode(const std::string &analyticalCode, int typeId) const
{
	if (typeId == 0)
	{
		std::string idSql = "SELECT oeav_at_id from oeav_analytical_types order by oeav_at_id desc limit 1";
		
		boost::shared_ptr<result> resultId =
			InstanceFactory<IConnection>::getInstance()->execute(idSql);

		if (resultId->empty())
			return;

		auto row = resultId->at(0);
		typeId = row[0].as<int>();
	}

		std::string sql{};
	
	sql += "INSERT INTO OEAV_ANALYTICAL_ACCOUNTING_CODES(oeav_analytical_code, oeav_analytical_type) VALUES('" + analyticalCode
		+ "', " + std::to_string(typeId) + ")";

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::addAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const
{
	std::string sql{};

	sql += "INSERT INTO OEAV_ANALYTICAL_TYPES(oeav_at_code, oeav_at_name) VALUES('" + analyticalCode
		+ "', '" + analyticalName + "')";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

boost::shared_ptr<AnalyticalTypeList> CardfilesRepository::getAnalyticalTypes() const
{
	std::string sql{ "SELECT * FROM OEAV_ANALYTICAL_TYPES ORDER BY oeav_at_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AnalyticalTypeList> analytList = boost::make_shared<AnalyticalTypeList>();

	for (auto row : *result)
		analytList->emplace_back(AnalyticalType(row[0].as<int>(), row[1].c_str(), row[2].c_str()));

	return analytList;
}

void CardfilesRepository::deleteAnalyticalType(int id) const
{
	std::string sql{ "DELETE FROM OEAV_ANALYTICAL_TYPES WHERE OEAV_AT_ID = '" + std::to_string(id) +  "'" };
	
	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::updateAnalyticalType(int id, const std::string &analyticalCode, const std::string &analyticalName) const
{
	std::string sql{ "UPDATE OEAV_ANALYTICAL_TYPES SET oeav_at_code = '" + analyticalCode + "', oeav_at_name = '" + analyticalName
		+ "' WHERE oeav_at_id= '" + std::to_string(id) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::deleteAnalyticalAccountCode(int typeId) const
{
	std::string sql{ "DELETE FROM OEAV_ANALYTICAL_ACCOUNTING_CODES WHERE oeav_id = '" + std::to_string(typeId) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::updateAnalyticalAccountCode(int itemId, int typeId, const std::string &analyticalCode) const
{
	std::string sql{ "UPDATE OEAV_ANALYTICAL_ACCOUNTING_CODES SET oeav_analytical_type = '" + std::to_string(typeId) + "',"
		" oeav_analytical_code = '" + analyticalCode + "' WHERE oeav_id = '" + std::to_string(itemId) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

boost::shared_ptr<AccountList> CardfilesRepository::getAccounts() const
{
	std::string sql{ "select * from oeav_accounts oa"
		" left join oeav_analytical_types oat on oa.oeav_a_analytical_type1 = oat.oeav_at_id"
		" left join oeav_analytical_types oat2 on oa.oeav_a_analytical_type2 = oat2.oeav_at_id"
		" order by oeav_a_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AccountList> accountList = boost::make_shared<AccountList>();
	
	for (auto row : *result)
	{
		accountList->emplace_back(Account(row[0].as<int>(), row[1].c_str(), row[5].c_str(),
			AccountTypes(row[2].as<int>()),
			AnalyticalType(row[6].is_null() ? 0 : row[6].as<int>(), row[7].is_null() ? "" : row[7].c_str(), row[8].is_null() ? "" : row[8].c_str()),
			AnalyticalType(row[9].is_null() ? 0 : row[9].as<int>(), row[10].is_null() ? "" : row[10].c_str(), row[11].is_null() ? "" : row[11].c_str())));
	}
		
	return accountList;
}

int CardfilesRepository::findIdByContent(const std::string &code, const std::string &name) const
{
	std::string sql{ "select oeav_at_id from oeav_analytical_types where oeav_at_code = '" + code + "' and oeav_at_name = '" + name + "'" };

	boost::shared_ptr<result> result = 
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	int id = 0;
	for (auto row : *result)
		if (!row[0].is_null())
			id = row[0].as<int>();

	return id;
}

void CardfilesRepository::updateAccount(int id, const std::string &code, const std::string &name,
	int typeId, int analyt1Id, int analyt2Id) const
{
	/*std::string sql{ "update oeav_accounts set oeav_a_code = '" + code + "',"
		" oeav_a_name = '" + name + "',"
		" oeav_a_account_type = '" + std::to_string(typeId) + "',"
		" oeav_a_analytical_type1 = '" + std::to_string(analyt1Id)
		+ "', oeav_a_analytical_type2 = '" + std::to_string(analyt2Id) + "'"
		"where oeav_a_id = '" + std::to_string(id) + "'" };*/

	std::string sql{ "update oeav_accounts set oeav_a_code = '" + code + "',"
		" oeav_a_name = '" + name + "'"};
	if (typeId && typeId != 0)
		sql += ", oeav_a_account_type = '" + std::to_string(typeId) + "'";
	if (analyt1Id && analyt1Id != 0)
		sql += ", oeav_a_analytical_type1 = '" + std::to_string(analyt1Id) + "'";
	if (analyt2Id && analyt2Id != 0)
		sql += ", oeav_a_analytical_type2 = '" + std::to_string(analyt2Id) + "'";
	sql += " where oeav_a_id = '" + std::to_string(id) + "'";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::addAccount(const std::string &code, const std::string &name,
	int typeId, int analyt1Id, int analyt2Id) const
{
	//if (analyt1Id == 0 && analyt2Id == 0 )
	//{
	//	std::string idSql = "SELECT oeav_at_id from oeav_analytical_types order by oeav_at_id limit 1";
	//	boost::shared_ptr<result> resultId =
	//		InstanceFactory<IConnection>::getInstance()->execute(idSql);

	//	if (resultId->empty())
	//		return;

	//	auto row = resultId->at(0);
	//	analyt1Id = row[0].as<int>();
	//	analyt2Id = analyt1Id;
	//}

	std::string sql{ "insert into oeav_accounts(oeav_a_code, oeav_a_name, oeav_a_account_type, oeav_a_analytical_type1,"
		" oeav_a_analytical_type2) values('" + code + "', '" + code + "', '" + std::to_string(typeId) + "', '" 
		+ std::to_string(analyt1Id) + "', '" + std::to_string(analyt2Id) + "')" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::deleteAccount(int id) const
{
	std::string sql{ "delete from oeav_accounts where oeav_a_id = '" + std::to_string(id) + "'" };
	
	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

boost::shared_ptr<PrimaryDocumentList> CardfilesRepository::getPrimaryDocuments() const
{
	std::string sql{ "select * from oeav_primary_documents pd"
		//" inner join oeav_analytical_types oat on pd.oeav_pd_at1 = oat.oeav_at_id"
		//" inner join oeav_analytical_types oat1 on pd.oeav_pd_at2 = oat1.oeav_at_id"
		//" inner join oeav_analytical_types oat2 on pd.oeav_pd_at3 = oat2.oeav_at_id"
		"order by oeav_pd_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<PrimaryDocumentList> pDocList = boost::make_shared<PrimaryDocumentList>();

	//int additionalId{};
	//std::string additionalCode{};
	//std::string additionalName{};
	for (auto row : *result)
	{
		//additionalId = {};
		//additionalCode = {};
		//additionalName = {};

		//if (row[15].is_null())
		//{
		//	additionalId = row[15].as<int>();
		//	additionalCode = row[16].c_str();
		//	additionalName = row[17].c_str();
		//}

		pDocList->emplace_back(PrimaryDocument(row[0].as<int>(), row[1].c_str(), row[2].c_str(), 
			AnalyticalType(row[9].as<int>(), row[10].c_str(), row[11].c_str()), AccountTypes(row[4].as<int>()),
			AnalyticalType(row[12].as<int>(), row[13].c_str(), row[14].c_str()), AccountTypes(row[6].as<int>()),
			AnalyticalType(row[15].as<int>(), row[16].c_str(), row[17].c_str()), AccountTypes(row[8].as<int>())
		));
	}

	return pDocList;
}

void CardfilesRepository::updatePrimaryDocument(int id, const std::string &code, const std::string &name, int analyt1,
	int type1, int analyt2, int type2, int analyt3, int type3) const
{
	std::string sql{ "update oeav_primary_documents set oeav_pd_code = '" + code + "',"
		" oeav_pd_name = '" + name + "',"
		" oeav_pd_at1 = '" + std::to_string(analyt1) + "',"
		" oeav_pd_at1_type = '" + std::to_string(type1) + "',"
		" oeav_pd_at2 = '" + std::to_string(analyt2) + "',"
		" oeav_pd_at2_type = '" + std::to_string(type2) + "',"
		" oeav_pd_at3 = '" + std::to_string(analyt3) + "',"
		" oeav_pd_at3_type = '" + std::to_string(type3) + "',"
		" where oeav_pd_id = '" + std::to_string(id) + "'"
	
	};

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::addPrimaryDocument(const std::string &code, const std::string &name, int analyt1,
	int type1, int analyt2, int type2, int analyt3, int type3) const
{
	if (analyt1 == 0 && analyt2 == 0 && analyt3 == 0)
	{
		std::string idSql = "SELECT oeav_at_id from oeav_analytical_types order by oeav_at_id limit 1";
		boost::shared_ptr<result> resultId =
			InstanceFactory<IConnection>::getInstance()->execute(idSql);

		if (resultId->empty())
			return;

		auto row = resultId->at(0);
		analyt1 = row[0].as<int>();
		analyt2 = analyt1;
		analyt3 = analyt1;
	}

	std::string sql{ "insert into oeav_primary_documents" };
}

void CardfilesRepository::deletePrimaryDocument(int id) const
{

}