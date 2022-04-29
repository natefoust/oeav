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
#include "../domain/typical_operation.h"

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
	std::string sql{ "insert into oeav_accounts(oeav_a_code, oeav_a_name, oeav_a_account_type, oeav_a_analytical_type1,"
		" oeav_a_analytical_type2) values('" + code + "', '" + name + "', '" + std::to_string(typeId) + "', '" 
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
		" left join oeav_analytical_types oat on pd.oeav_pd_at1 = oat.oeav_at_id"
		" left join oeav_analytical_types oat1 on pd.oeav_pd_at2 = oat1.oeav_at_id"
		" left join oeav_analytical_types oat2 on pd.oeav_pd_at3 = oat2.oeav_at_id"
		" order by oeav_pd_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<PrimaryDocumentList> pDocList = boost::make_shared<PrimaryDocumentList>();

	for (auto row : *result)
	{
		pDocList->emplace_back(PrimaryDocument(row[0].as<int>(), row[1].c_str(), row[2].c_str(), 
			AnalyticalType(row[9].is_null() ? 0 : row[9].as<int>(), row[10].is_null() ? "" : row[10].c_str(), row[11].is_null() ? "" : row[11].c_str()), AccountTypes(row[4].as<int>()),
			AnalyticalType(row[12].is_null() ? 0 : row[12].as<int>(), row[13].is_null() ? "" : row[13].c_str(), row[14].is_null() ? "" : row[14].c_str()), AccountTypes(row[6].as<int>()),
			AnalyticalType(row[15].is_null() ? 0 : row[15].as<int>(), row[16].is_null() ? "" : row[16].c_str(), row[17].is_null() ? "" : row[17].c_str()), AccountTypes(row[8].as<int>())
		));
	}

	return pDocList;
}

boost::shared_ptr<PrimaryDocument> CardfilesRepository::getPrimaryDocument(int docId) const
{
	std::string sql{ "select * from oeav_primary_documents pd"
		" left join oeav_analytical_types oat on pd.oeav_pd_at1 = oat.oeav_at_id"
		" left join oeav_analytical_types oat1 on pd.oeav_pd_at2 = oat1.oeav_at_id"
		" left join oeav_analytical_types oat2 on pd.oeav_pd_at3 = oat2.oeav_at_id"
		" where oeav_pd_id = '" + std::to_string(docId) + "'"
		" order by oeav_pd_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<PrimaryDocument> pDoc = boost::make_shared<PrimaryDocument>();

	for (auto row : *result)
	{
		pDoc = boost::make_shared<PrimaryDocument>(PrimaryDocument(row[0].as<int>(), row[1].c_str(), row[2].c_str(),
			AnalyticalType(row[9].is_null() ? 0 : row[9].as<int>(), row[10].is_null() ? "" : row[10].c_str(), row[11].is_null() ? "" : row[11].c_str()), AccountTypes(row[4].as<int>()),
			AnalyticalType(row[12].is_null() ? 0 : row[12].as<int>(), row[13].is_null() ? "" : row[13].c_str(), row[14].is_null() ? "" : row[14].c_str()), AccountTypes(row[6].as<int>()),
			AnalyticalType(row[15].is_null() ? 0 : row[15].as<int>(), row[16].is_null() ? "" : row[16].c_str(), row[17].is_null() ? "" : row[17].c_str()), AccountTypes(row[8].as<int>())
		));
	}

	return pDoc;
}

void CardfilesRepository::updatePrimaryDocument(int id, const std::string &code, const std::string &name, int analyt1,
	int type1, int analyt2, int type2, int analyt3, int type3) const
{
	std::string sql{ "update oeav_primary_documents set oeav_pd_code = '" + code + "',"
		" oeav_pd_name = '" + name + "'" };
	if (analyt1 && analyt1 != 0)
		sql += ", oeav_pd_at1 = '" + std::to_string(analyt1) + "'";
	if (type1 && type1 != 0)
		sql += ", oeav_pd_at1_type = '" + std::to_string(type1) + "'";
	if (analyt2 && analyt2 != 0)
		sql += ", oeav_pd_at2 = '" + std::to_string(analyt2) + "'";
	if (type2 && type2 != 0)
		sql += ", oeav_pd_at2_type = '" + std::to_string(type2) + "'";
	if (analyt3 && analyt3 != 0)
		sql += ", oeav_pd_at3 = '" + std::to_string(analyt3) + "'";
	if (type3 && type3 != 0)
		sql += ", oeav_pd_at3_type = '" + std::to_string(type3) + "'";
	sql += " where oeav_pd_id = '" + std::to_string(id) + "'";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::addPrimaryDocument(const std::string &code, const std::string &name, int analyt1,
	int type1, int analyt2, int type2, int analyt3, int type3) const
{
	std::string sql{ "insert into oeav_primary_documents(oeav_pd_code, oeav_pd_name, oeav_pd_at1, oeav_pd_at1_type, oeav_pd_at2, oeav_pd_at2_type, oeav_pd_at3, oeav_pd_at3_type)"
		" values('" + code + "', '" + name + "', '" + std::to_string(analyt1) + "', '"
		+ std::to_string(type1) + "', '" + std::to_string(analyt2) + "', '" + std::to_string(type2) + 
		"', '" + std::to_string(analyt3) + "', '" + std::to_string(type3) + "')" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::deletePrimaryDocument(int id) const
{
	std::string sql{ "delete from oeav_primary_documents where oeav_pd_id = '" + std::to_string(id) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

boost::shared_ptr<TypicalOperationList> CardfilesRepository::getTypicalOperations() const
{
	std::string sql{ "select * from oeav_typical_operations top"
		" left join oeav_primary_documents pd on top.oeav_to_doc_code = pd.oeav_pd_id"
		" left join oeav_analytical_types oat on pd.oeav_pd_at1 = oat.oeav_at_id"
		" left join oeav_analytical_types oat1 on pd.oeav_pd_at2 = oat1.oeav_at_id"
		" left join oeav_analytical_types oat2 on pd.oeav_pd_at3 = oat2.oeav_at_id"
		" left join oeav_accounts a on top.oeav_to_debet = a.oeav_a_id"
		" left join oeav_analytical_types oat3 on a.oeav_a_analytical_type1 = oat3.oeav_at_id"
		" left join oeav_analytical_types oat4 on a.oeav_a_analytical_type1 = oat4.oeav_at_id"
		" left join oeav_accounts a1 on top.oeav_to_credit = a1.oeav_a_id"
		" left join oeav_analytical_types oat5 on a1.oeav_a_analytical_type1 = oat5.oeav_at_id"
		" left join oeav_analytical_types oat6 on a1.oeav_a_analytical_type1 = oat6.oeav_at_id"
		" order by oeav_to_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<TypicalOperationList> tOpList = boost::make_shared<TypicalOperationList>();

	for (auto row : *result)
	{
		tOpList->emplace_back(TypicalOperation(row[0].as<int>(),
			PrimaryDocument(row[5].is_null() ? 0 : row[5].as<int>(), row[6].is_null() ? "" : row[6].c_str(),
				row[7].is_null() ? "" : row[7].c_str(), AnalyticalType(row[14].is_null() ? 0 : row[14].as<int>(), row[15].is_null() ? "" : row[15].c_str(),
				row[16].is_null() ? "" : row[16].c_str()), AccountTypes(row[8].is_null() ? 0 : row[8].as<int>()), AnalyticalType(row[17].is_null() ? 0 : row[17].as<int>(),
					row[18].is_null() ? "" : row[18].c_str(), row[19].is_null() ? "" : row[19].c_str()), AccountTypes(row[10].is_null() ? 0 : row[10].as<int>()),
				AnalyticalType(row[20].is_null() ? 0 : row[20].as<int>(), row[21].is_null() ? "" : row[21].c_str(), row[22].is_null() ? "" : row[22].c_str()),
				AccountTypes(row[12].is_null() ? 0 : row[12].as<int>())),
			row[2].c_str(),
			Account(row[23].is_null() ? 0 : row[23].as<int>(), row[24].is_null() ? "" : row[24].c_str(), row[28].is_null() ? "" : row[28].c_str(), AccountTypes(row[25].is_null() ? 0 : row[25].as<int>()),
				AnalyticalType(row[29].is_null() ? 0 : row[29].as<int>(), row[30].is_null() ? "" : row[30].c_str(), row[31].is_null() ? "" : row[31].c_str()), 
				AnalyticalType(row[32].is_null() ? 0 : row[32].as<int>(), row[33].is_null() ? "" : row[33].c_str(), row[34].is_null() ? "" : row[34].c_str())),
			Account(row[35].is_null() ? 0 : row[35].as<int>(), row[36].is_null() ? "" : row[36].c_str(), row[40].is_null() ? "" : row[40].c_str(), AccountTypes(row[37].is_null() ? 0 : row[37].as<int>()),
				AnalyticalType(row[41].is_null() ? 0 : row[41].as<int>(), row[42].is_null() ? "" : row[42].c_str(), row[43].is_null() ? "" : row[43].c_str()),
				AnalyticalType(row[44].is_null() ? 0 : row[44].as<int>(), row[45].is_null() ? "" : row[45].c_str(), row[46].is_null() ? "" : row[46].c_str()))

			));
	}

	return tOpList;
}

boost::shared_ptr<TypicalOperationList> CardfilesRepository::getTypicalOperationsByDocId(int docId) const
{
	std::string sql{ "select * from oeav_typical_operations top"
		" left join oeav_primary_documents pd on top.oeav_to_doc_code = pd.oeav_pd_id"
		" left join oeav_analytical_types oat on pd.oeav_pd_at1 = oat.oeav_at_id"
		" left join oeav_analytical_types oat1 on pd.oeav_pd_at2 = oat1.oeav_at_id"
		" left join oeav_analytical_types oat2 on pd.oeav_pd_at3 = oat2.oeav_at_id"
		" left join oeav_accounts a on top.oeav_to_debet = a.oeav_a_id"
		" left join oeav_analytical_types oat3 on a.oeav_a_analytical_type1 = oat3.oeav_at_id"
		" left join oeav_analytical_types oat4 on a.oeav_a_analytical_type1 = oat4.oeav_at_id"
		" left join oeav_accounts a1 on top.oeav_to_credit = a1.oeav_a_id"
		" left join oeav_analytical_types oat5 on a1.oeav_a_analytical_type1 = oat5.oeav_at_id"
		" left join oeav_analytical_types oat6 on a1.oeav_a_analytical_type1 = oat6.oeav_at_id"
		" where oeav_to_doc_code = '" + std::to_string(docId) + "'"
		" order by oeav_to_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<TypicalOperationList> tOpList = boost::make_shared<TypicalOperationList>();

	for (auto row : *result)
	{
		tOpList->emplace_back(TypicalOperation(row[0].as<int>(),
			PrimaryDocument(row[5].is_null() ? 0 : row[5].as<int>(), row[6].is_null() ? "" : row[6].c_str(),
				row[7].is_null() ? "" : row[7].c_str(), AnalyticalType(row[14].is_null() ? 0 : row[14].as<int>(), row[15].is_null() ? "" : row[15].c_str(),
					row[16].is_null() ? "" : row[16].c_str()), AccountTypes(row[8].is_null() ? 0 : row[8].as<int>()), AnalyticalType(row[17].is_null() ? 0 : row[17].as<int>(),
						row[18].is_null() ? "" : row[18].c_str(), row[19].is_null() ? "" : row[19].c_str()), AccountTypes(row[10].is_null() ? 0 : row[10].as<int>()),
				AnalyticalType(row[20].is_null() ? 0 : row[20].as<int>(), row[21].is_null() ? "" : row[21].c_str(), row[22].is_null() ? "" : row[22].c_str()),
				AccountTypes(row[12].is_null() ? 0 : row[12].as<int>())),
			row[2].c_str(),
			Account(row[23].is_null() ? 0 : row[23].as<int>(), row[24].is_null() ? "" : row[24].c_str(), row[28].is_null() ? "" : row[28].c_str(), AccountTypes(row[25].is_null() ? 0 : row[25].as<int>()),
				AnalyticalType(row[29].is_null() ? 0 : row[29].as<int>(), row[30].is_null() ? "" : row[30].c_str(), row[31].is_null() ? "" : row[31].c_str()),
				AnalyticalType(row[32].is_null() ? 0 : row[32].as<int>(), row[33].is_null() ? "" : row[33].c_str(), row[34].is_null() ? "" : row[34].c_str())),
			Account(row[35].is_null() ? 0 : row[35].as<int>(), row[36].is_null() ? "" : row[36].c_str(), row[40].is_null() ? "" : row[40].c_str(), AccountTypes(row[37].is_null() ? 0 : row[37].as<int>()),
				AnalyticalType(row[41].is_null() ? 0 : row[41].as<int>(), row[42].is_null() ? "" : row[42].c_str(), row[43].is_null() ? "" : row[43].c_str()),
				AnalyticalType(row[44].is_null() ? 0 : row[44].as<int>(), row[45].is_null() ? "" : row[45].c_str(), row[46].is_null() ? "" : row[46].c_str()))

		));
	}

	return tOpList;
}

void CardfilesRepository::updateTypicalOperation(int id, int docId, const std::string &name, int debetId, int creditId) const
{
	std::string sql{ "update oeav_typical_operations set oeav_to_operation_name = '" + name + "'" };
	if (docId && docId != 0)
		sql += " , oeav_to_doc_code = '" + std::to_string(docId) + "'";
	if (debetId && debetId != 0)
		sql += " , oeav_to_debet = '" + std::to_string(debetId) + "'";
	if (creditId && creditId != 0)
		sql += " , oeav_to_credit = '" + std::to_string(creditId) + "'";
	sql += " where oeav_to_id = '" + std::to_string(id) + "'";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::addTypicalOperation(int docId, const std::string &name, int debetIt, int creditId) const
{
	std::string sql{ "insert into oeav_typical_operations(oeav_to_doc_code, oeav_to_operation_name, oeav_to_debet, oeav_to_credit)"
		" values('" + std::to_string(docId) + "', '" + name + "', '" + std::to_string(debetIt) + "', '"
		+ std::to_string(creditId) + "')" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::deleteTypicalOperation(int id) const
{
	std::string sql{ "delete from oeav_typical_operations where oeav_to_id = '" + std::to_string(id) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

int CardfilesRepository::findAccIdByContent(const std::string &code, const std::string &name) const
{
	std::string sql{ "select oeav_a_id from oeav_accounts where oeav_a_code = '" + code + "' and oeav_a_name = '" + name + "'" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	int id = 0;
	for (auto row : *result)
		if (!row[0].is_null())
			id = row[0].as<int>();

	return id;
}

int CardfilesRepository::findOpdIdByContent(const std::string &code, const std::string &name) const
{
	std::string sql{ "select oeav_pd_id from oeav_primary_documents where oeav_pd_code = '" + code + "' and oeav_pd_name = '" + name + "'" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	int id = 0;
	for (auto row : *result)
		if (!row[0].is_null())
			id = row[0].as<int>();

	return id;
}

boost::shared_ptr<AnalyticalAccountingCode> CardfilesRepository::getAnalyticalAccountingCode(int atId) const
{
	std::string sql{ "SELECT * FROM OEAV_ANALYTICAL_ACCOUNTING_CODES OAAC INNER JOIN OEAV_ANALYTICAL_TYPES OAT"
		" ON OAAC.OEAV_ANALYTICAL_TYPE = OAT.OEAV_AT_ID where oeav_id = '" + std::to_string(atId) + "' ORDER BY oeav_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AnalyticalAccountingCode> analytCode = boost::make_shared<AnalyticalAccountingCode>();

	for (auto row : *result)
		analytCode = boost::make_shared<AnalyticalAccountingCode>(AnalyticalAccountingCode(row[0].as<int>(), 0, AnalyticalType(row[4].as<int>(), row[5].c_str(),
			row[6].c_str()), row[3].c_str()));

	return analytCode;
}

boost::shared_ptr<AnalyticalAccountingCodeList> CardfilesRepository::getAnalyticalAccountingCodes(int atId) const
{
	std::string sql{ "SELECT * FROM OEAV_ANALYTICAL_ACCOUNTING_CODES OAAC INNER JOIN OEAV_ANALYTICAL_TYPES OAT"
		" ON OAAC.OEAV_ANALYTICAL_TYPE = OAT.OEAV_AT_ID where oeav_analytical_type = '" + std::to_string(atId) + "' ORDER BY oeav_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AnalyticalAccountingCodeList> analytCodesList = boost::make_shared<AnalyticalAccountingCodeList>();

	for (auto row : *result)
		analytCodesList->emplace_back(AnalyticalAccountingCode(row[0].as<int>(), 0, AnalyticalType(row[4].as<int>(), row[5].c_str(),
			row[6].c_str()), row[3].c_str()));

	return analytCodesList;
}