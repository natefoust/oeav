#pragma once

#include "oeav_cardfiles_repository.h"

#include <boost/make_shared.hpp>
#include <pqxx/pqxx>
#include <sstream>

#include "../shared/oeav_iconnection.h"
#include "../shared/oeav_instance_factory.h"

#include "../domain/oeav_analytical_type.h"
#include "../domain/oeav_analytical_accounting_code.h"
#include "../domain/oeav_account.h"
#include "../domain/oeav_primary_document.h"
#include "../domain/oeav_typical_operation.h"

using namespace oeav::domain;
using namespace pqxx;

// coalesce used because we need to store empty objects (or empty fields)

boost::shared_ptr<AnalyticalAccountingCodeList> CardfilesRepository::getAnalyticalAccountingCodes() const
{
	std::string sql{ "SELECT oeav_kau_id, oeav_kau_0, coalesce(oeav_kau_v, 0) as oeav_kau_v, coalesce(oeav_kau_k, '') as oeav_kau_k,"
		" coalesce(oeav_va_id, 0) as oeav_va_id, coalesce(oeav_va_k, '') as oeav_va_k, coalesce(oeav_va_n, '') as oeav_va_n"
		" FROM oeav_kau OAAC INNER JOIN oeav_va OAT"
		" ON OAAC.oeav_kau_v = OAT.oeav_va_id ORDER BY oeav_kau_id" };

	boost::shared_ptr<result> result = 
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AnalyticalAccountingCodeList> analytCodesList = boost::make_shared<AnalyticalAccountingCodeList>();

	for (auto row : *result)
		analytCodesList->emplace_back(AnalyticalAccountingCode(row.at("oeav_kau_id").as<int>(), row.at("oeav_kau_0").as<int>(), 
			AnalyticalType(row.at("oeav_va_id").as<int>(), row.at("oeav_va_k").c_str(),
			row.at("oeav_va_n").c_str()), row.at("oeav_kau_k").c_str()));

	return analytCodesList;
}

void CardfilesRepository::addAnalyticalAccountingCode(const std::string &analyticalCode, int typeId) const
{
	if (typeId == 0)
	{
		std::string idSql = "SELECT oeav_va_id from oeav_va order by oeav_va_id desc limit 1";
		
		boost::shared_ptr<result> resultId =
			InstanceFactory<IConnection>::getInstance()->execute(idSql);

		if (resultId->empty())
			return;

		auto row = resultId->at(0);
		typeId = row[0].as<int>();
	}

		std::string sql{};
	
	sql += "INSERT INTO oeav_kau(oeav_kau_k, oeav_kau_v) VALUES('" + analyticalCode
		+ "', " + std::to_string(typeId) + ")";

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::addAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const
{
	std::string sql{};

	sql += "INSERT INTO oeav_va(oeav_va_k, oeav_va_n) VALUES('" + analyticalCode
		+ "', '" + analyticalName + "')";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

boost::shared_ptr<AnalyticalTypeList> CardfilesRepository::getAnalyticalTypes() const
{
	std::string sql{ "SELECT oeav_va_id, oeav_va_0, coalesce(oeav_va_k, '') as oeav_va_k, coalesce(oeav_va_n, '') as oeav_va_n"
					 " FROM oeav_va ORDER BY oeav_va_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AnalyticalTypeList> analytList = boost::make_shared<AnalyticalTypeList>();

	for (auto row : *result)
		analytList->emplace_back(AnalyticalType(row.at("oeav_va_id").as<int>(), row.at("oeav_va_k").c_str(), row.at("oeav_va_n").c_str()));

	return analytList;
}

void CardfilesRepository::deleteAnalyticalType(int id) const
{
	std::string sql{ "DELETE FROM oeav_va WHERE oeav_va_id = '" + std::to_string(id) +  "'" };
	
	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::updateAnalyticalType(int id, const std::string &analyticalCode, const std::string &analyticalName) const
{
	std::string sql{ "UPDATE oeav_va SET oeav_va_k = '" + analyticalCode + "', oeav_va_n = '" + analyticalName
		+ "' WHERE oeav_va_id= '" + std::to_string(id) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::deleteAnalyticalAccountCode(int typeId) const
{
	std::string sql{ "DELETE FROM oeav_kau WHERE oeav_kau_id = '" + std::to_string(typeId) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::updateAnalyticalAccountCode(int itemId, int typeId, const std::string &analyticalCode) const
{
	std::string sql{ "UPDATE oeav_kau SET oeav_kau_v = '" + std::to_string(typeId) + "',"
		" oeav_kau_k = '" + analyticalCode + "' WHERE oeav_kau_id = '" + std::to_string(itemId) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

boost::shared_ptr<AccountList> CardfilesRepository::getAccounts() const
{
	std::string sql{ "select oeav_ps_id, oeav_ps_0, coalesce(oeav_ps_s, '') as oeav_ps_s, coalesce(oeav_ps_n, '') as oeav_ps_n , coalesce(oeav_ps_typ, '0') as oeav_ps_typ , coalesce(oat.oeav_va_id, 0) as id1, coalesce(oat.oeav_va_k, '') as code1, coalesce(oat.oeav_va_n, '') as name1 ,"
		" coalesce(oat2.oeav_va_id, 0) as id2, coalesce(oat2.oeav_va_k, '') as code2, coalesce(oat2.oeav_va_n, '') as name2 from oeav_ps as oa"
		" left join oeav_va oat on oa.oeav_ps_av1 = oat.oeav_va_id"
		" left join oeav_va oat2 on oa.oeav_ps_av2 = oat2.oeav_va_id"
		" order by oeav_ps_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AccountList> accountList = boost::make_shared<AccountList>();
	
	for (auto row : *result)
	{
		std::stringstream ss;
		ss << row.at("oeav_ps_id").as<int>();
		ss << row.at("id1").as<int>();

		accountList->emplace_back(Account(row.at("oeav_ps_id").as<int>(), row.at("oeav_ps_n").c_str(), row.at("oeav_ps_s").c_str(),
		AccountTypes(row.at("oeav_ps_typ").as<int>()),
		AnalyticalType(row.at("id1").as<int>(), row.at("code1").c_str(), row.at("name1").c_str()),
		AnalyticalType(row.at("id2").as<int>(), row.at("code2").c_str(), row.at("name2").c_str())));
	}
		
	return accountList;
}

int CardfilesRepository::findIdByContent(const std::string &code, const std::string &name) const
{
	std::string sql{ "select oeav_va_id from oeav_va where oeav_va_k = '" + code + "' and oeav_va_n = '" + name + "'" };

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
	std::string sql{ "update oeav_ps set oeav_ps_s = '" + code + "',"
		" oeav_ps_n = '" + name + "'" };
	if (typeId && typeId != 0)
		sql += ", oeav_ps_typ = '" + std::to_string(typeId) + "'";
	if (analyt1Id && analyt1Id != 0)
		sql += ", oeav_ps_av1 = '" + std::to_string(analyt1Id) + "'";
	if (analyt2Id && analyt2Id != 0)
		sql += ", oeav_ps_av2 = '" + std::to_string(analyt2Id) + "'";
	sql += " where oeav_ps_id = '" + std::to_string(id) + "'";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::addAccount(const std::string &code, const std::string &name,
	int typeId, int analyt1Id, int analyt2Id) const
{
	std::string sql{ "insert into oeav_ps(oeav_ps_s, oeav_ps_n, oeav_ps_typ, oeav_ps_av1,"
		" oeav_ps_av2) values('" + code + "', '" + name + "', '" + std::to_string(typeId) + "', '" 
		+ std::to_string(analyt1Id) + "', '" + std::to_string(analyt2Id) + "')" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::deleteAccount(int id) const
{
	std::string sql{ "delete from oeav_ps where oeav_ps_id = '" + std::to_string(id) + "'" };
	
	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

boost::shared_ptr<PrimaryDocumentList> CardfilesRepository::getPrimaryDocuments() const
{
	std::string sql{ "select oeav_opd_id, coalesce(oeav_opd_k, '') as oeav_opd_k, coalesce(oeav_opd_n, '') as oeav_opd_n, "
			" coalesce(oat.oeav_va_id, 0) as oeav_vid1, coalesce(oat.oeav_va_k, '') as oeav_vk1, coalesce(oat.oeav_va_n, '') as oeav_vn1,"
			" coalesce(oeav_opd_avt1, '0') as oeav_opd_avt1, "
			" coalesce(oat1.oeav_va_id, 0) as oeav_vid2, coalesce(oat1.oeav_va_k, '') as oeav_vk2, coalesce(oat1.oeav_va_n, '') as oeav_vn2,"
			" coalesce(oeav_opd_avt2, '0') as oeav_opd_avt2, "
			" coalesce(oat2.oeav_va_id, 0) as oeav_vid3, coalesce(oat2.oeav_va_k, '') as oeav_vk3, coalesce(oat2.oeav_va_n, '') as oeav_vn3,"
			" coalesce(oeav_opd_avt3, '0') as oeav_opd_avt3 "
			" from oeav_opd pd"
			" left join oeav_va oat on pd.oeav_opd_av1 = oat.oeav_va_id"
			" left join oeav_va oat1 on pd.oeav_opd_av2 = oat1.oeav_va_id"
			" left join oeav_va oat2 on pd.oeav_opd_av3 = oat2.oeav_va_id"
			" order by oeav_opd_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<PrimaryDocumentList> pDocList = boost::make_shared<PrimaryDocumentList>();

	for (auto row : *result)
	{
		pDocList->emplace_back(PrimaryDocument(row.at("oeav_opd_id").as<int>(), row.at("oeav_opd_k").c_str(), row.at("oeav_opd_n").c_str(),
			AnalyticalType(row.at("oeav_vid1").as<int>(), row.at("oeav_vk1").c_str(), row.at("oeav_vn1").c_str()), AccountTypes(row.at("oeav_opd_avt1").as<int>()),
			AnalyticalType(row.at("oeav_vid2").as<int>(), row.at("oeav_vk2").c_str(), row.at("oeav_vn2").c_str()), AccountTypes(row.at("oeav_opd_avt2").as<int>()),
			AnalyticalType(row.at("oeav_vid3").as<int>(), row.at("oeav_vk3").c_str(), row.at("oeav_vn3").c_str()), AccountTypes(row.at("oeav_opd_avt3").as<int>())
		));
	}

	return pDocList;
}

boost::shared_ptr<PrimaryDocument> CardfilesRepository::getPrimaryDocument(int docId) const
{
	std::string sql{ "select oeav_opd_id, coalesce(oeav_opd_k, '') as oeav_opd_k, coalesce(oeav_opd_n, '') as oeav_opd_n, "
			" coalesce(oat.oeav_va_id, 0) as oeav_vid1, coalesce(oat.oeav_va_k, '') as oeav_vk1, coalesce(oat.oeav_va_n, '') as oeav_vn1,"
			" coalesce(oeav_opd_avt1, '0') as oeav_opd_avt1, "
			" coalesce(oat1.oeav_va_id, 0) as oeav_vid2, coalesce(oat1.oeav_va_k, '') as oeav_vk2, coalesce(oat1.oeav_va_n, '') as oeav_vn2,"
			" coalesce(oeav_opd_avt2, '0') as oeav_opd_avt2, "
			" coalesce(oat2.oeav_va_id, 0) as oeav_vid3, coalesce(oat2.oeav_va_k, '') as oeav_vk3, coalesce(oat2.oeav_va_n, '') as oeav_vn3,"
			" coalesce(oeav_opd_avt3, '0') as oeav_opd_avt3 "
			" from oeav_opd pd"
			" left join oeav_va oat on pd.oeav_opd_av1 = oat.oeav_va_id"
			" left join oeav_va oat1 on pd.oeav_opd_av2 = oat1.oeav_va_id"
			" left join oeav_va oat2 on pd.oeav_opd_av3 = oat2.oeav_va_id"
			" where oeav_opd_id = '" + std::to_string(docId) + "'"
			" order by oeav_opd_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<PrimaryDocument> pDoc = boost::make_shared<PrimaryDocument>();

	for (auto row : *result)
	{
		pDoc = boost::make_shared<PrimaryDocument>(PrimaryDocument(row.at("oeav_opd_id").as<int>(), row.at("oeav_opd_k").c_str(), row.at("oeav_opd_n").c_str(),
			AnalyticalType(row.at("oeav_vid1").as<int>(), row.at("oeav_vk1").c_str(), row.at("oeav_vn1").c_str()), AccountTypes(row.at("oeav_opd_avt1").as<int>()),
			AnalyticalType(row.at("oeav_vid2").as<int>(), row.at("oeav_vk2").c_str(), row.at("oeav_vn2").c_str()), AccountTypes(row.at("oeav_opd_avt2").as<int>()),
			AnalyticalType(row.at("oeav_vid3").as<int>(), row.at("oeav_vk3").c_str(), row.at("oeav_vn3").c_str()), AccountTypes(row.at("oeav_opd_avt3").as<int>())
		));
	}

	return pDoc;
}

void CardfilesRepository::updatePrimaryDocument(int id, const std::string &code, const std::string &name, int analyt1,
	int type1, int analyt2, int type2, int analyt3, int type3) const
{
	std::string sql{ "update oeav_opd set oeav_opd_k = '" + code + "',"
		" oeav_opd_n = '" + name + "'" };
	if (analyt1 && analyt1 != 0)
		sql += ", oeav_opd_av1 = '" + std::to_string(analyt1) + "'";
	if (type1 && type1 != 0)
		sql += ", oeav_opd_avt1 = '" + std::to_string(type1) + "'";
	if (analyt2 && analyt2 != 0)
		sql += ", oeav_opd_av2 = '" + std::to_string(analyt2) + "'";
	if (type2 && type2 != 0)
		sql += ", oeav_opd_avt2 = '" + std::to_string(type2) + "'";
	if (analyt3 && analyt3 != 0)
		sql += ", oeav_opd_av3 = '" + std::to_string(analyt3) + "'";
	if (type3 && type3 != 0)
		sql += ", oeav_opd_avt3 = '" + std::to_string(type3) + "'";
	sql += " where oeav_opd_id = '" + std::to_string(id) + "'";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::addPrimaryDocument(const std::string &code, const std::string &name, int analyt1,
	int type1, int analyt2, int type2, int analyt3, int type3) const
{
	std::string sql{ "insert into oeav_opd(oeav_opd_k, oeav_opd_n, oeav_opd_av1, oeav_opd_avt1, oeav_opd_av2, oeav_opd_avt2, oeav_opd_av3, oeav_opd_avt3)"
		" values('" + code + "', '" + name + "', '" + std::to_string(analyt1) + "', '"
		+ std::to_string(type1) + "', '" + std::to_string(analyt2) + "', '" + std::to_string(type2) + 
		"', '" + std::to_string(analyt3) + "', '" + std::to_string(type3) + "')" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::deletePrimaryDocument(int id) const
{
	std::string sql{ "delete from oeav_opd where oeav_opd_id = '" + std::to_string(id) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

boost::shared_ptr<TypicalOperationList> CardfilesRepository::getTypicalOperations() const
{
	std::string sql{ "select oeav_txo_id, oeav_txo_0, coalesce(oeav_opd_id, 0) as oeav_opd_id, coalesce(oeav_opd_k, '') as oeav_opd_k, coalesce(oeav_opd_n, '') as oeav_opd_n,"
					" coalesce(oat.oeav_va_id, 0) as oeav_vid1, coalesce(oat.oeav_va_k, '') as oeav_vk1, coalesce(oat.oeav_va_n, '') as oeav_vn1,"
					" coalesce(oeav_opd_avt1, '0') as oeav_opd_avt1,"
					" coalesce(oat1.oeav_va_id, 0) as oeav_vid2, coalesce(oat1.oeav_va_k, '') as oeav_vk2, coalesce(oat1.oeav_va_n, '') as oeav_vn2,"
					" coalesce(oeav_opd_avt2, '0') as oeav_opd_avt2,"
					" coalesce(oat2.oeav_va_id, 0) as oeav_vid3, coalesce(oat2.oeav_va_k, '') as oeav_vk3, coalesce(oat2.oeav_va_n, '') as oeav_vn3,"
					" coalesce(oeav_opd_avt3, '0') as oeav_opd_avt3,"
					" coalesce(oeav_txo_k, '') as oeav_txo_k, "
					" coalesce(a.oeav_ps_id, 0) as oeav_sid1, coalesce(a.oeav_ps_n, '') as oeav_sn1, coalesce(a.oeav_ps_s, '') as oeav_sk1, coalesce(a.oeav_ps_typ, '0') as oeav_styp1,"
					" coalesce(oat3.oeav_va_id, 0) as oeav_vid4, coalesce(oat3.oeav_va_k, '') as oeav_vk4, coalesce(oat3.oeav_va_n, '') as oeav_vn4,"
					" coalesce(oat4.oeav_va_id, 0) as oeav_vid5, coalesce(oat4.oeav_va_k, '') as oeav_vk5, coalesce(oat4.oeav_va_n, '') as oeav_vn5,"
					" coalesce(a1.oeav_ps_id, 0) as oeav_sid2, coalesce(a1.oeav_ps_n, '') as oeav_sn2, coalesce(a1.oeav_ps_s, '') as oeav_sk2, coalesce(a1.oeav_ps_typ, '0') as oeav_styp2,"
					" coalesce(oat5.oeav_va_id, 0) as oeav_vid6, coalesce(oat5.oeav_va_k, '') as oeav_vk6, coalesce(oat5.oeav_va_n, '') as oeav_vn6,"
					" coalesce(oat6.oeav_va_id, 0) as oeav_vid7, coalesce(oat6.oeav_va_k, '') as oeav_vk7, coalesce(oat6.oeav_va_n, '') as oeav_vn7"
		
					" from oeav_txo top"
					" left join oeav_opd pd on top.oeav_txo_dokk = pd.oeav_opd_id"
					" left join oeav_va oat on pd.oeav_opd_av1 = oat.oeav_va_id"
					" left join oeav_va oat1 on pd.oeav_opd_av2 = oat1.oeav_va_id"
					" left join oeav_va oat2 on pd.oeav_opd_av3 = oat2.oeav_va_id"
					" left join oeav_ps a on top.oeav_txo_db = a.oeav_ps_id"
					" left join oeav_va oat3 on a.oeav_ps_av1 = oat3.oeav_va_id"
					" left join oeav_va oat4 on a.oeav_ps_av1 = oat4.oeav_va_id"
					" left join oeav_ps a1 on top.oeav_txo_kr = a1.oeav_ps_id"
					" left join oeav_va oat5 on a1.oeav_ps_av1 = oat5.oeav_va_id"
					" left join oeav_va oat6 on a1.oeav_ps_av1 = oat6.oeav_va_id"
					" order by oeav_txo_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<TypicalOperationList> tOpList = boost::make_shared<TypicalOperationList>();

	
	for (auto row : *result)
	{
		tOpList->emplace_back(TypicalOperation(row.at("oeav_txo_id").as<int>(),
			PrimaryDocument(row.at("oeav_opd_id").as<int>(), row.at("oeav_opd_k").c_str(),
				row.at("oeav_opd_n").c_str(), 
				AnalyticalType(row.at("oeav_vid1").as<int>(), row.at("oeav_vk1").c_str(), row.at("oeav_vn1").c_str()), 
				AccountTypes(row.at("oeav_opd_avt1").as<int>()), 
				AnalyticalType(row.at("oeav_vid2").as<int>(), row.at("oeav_vk2").c_str(), row.at("oeav_vn2").c_str()),
				AccountTypes(row.at("oeav_opd_avt2").as<int>()),
				AnalyticalType(row.at("oeav_vid3").as<int>(), row.at("oeav_vk3").c_str(), row.at("oeav_vn3").c_str()),
				AccountTypes(row.at("oeav_opd_avt3").as<int>())),
			row.at("oeav_txo_k").c_str(),
			Account(row.at("oeav_sid1").as<int>(), row.at("oeav_sn1").c_str(), row.at("oeav_sk1").c_str(), AccountTypes(row.at("oeav_styp1").as<int>()),
				AnalyticalType(row.at("oeav_vid4").as<int>(), row.at("oeav_vk4").c_str(), row.at("oeav_vn4").c_str()),
				AnalyticalType(row.at("oeav_vid5").as<int>(), row.at("oeav_vk5").c_str(), row.at("oeav_vn5").c_str())),
			Account(row.at("oeav_sid2").as<int>(), row.at("oeav_sn2").c_str(), row.at("oeav_sk2").c_str(), AccountTypes(row.at("oeav_styp2").as<int>()),
				AnalyticalType(row.at("oeav_vid6").as<int>(), row.at("oeav_vk6").c_str(), row.at("oeav_vn6").c_str()),
				AnalyticalType(row.at("oeav_vid7").as<int>(), row.at("oeav_vk7").c_str(), row.at("oeav_vn7").c_str()))
			));
	}

	return tOpList;
}

boost::shared_ptr<TypicalOperationList> CardfilesRepository::getTypicalOperationsByDocId(int docId) const
{
	std::string sql{ "select oeav_txo_id, oeav_txo_0, coalesce(oeav_opd_id, 0) as oeav_opd_id, coalesce(oeav_opd_k, '') as oeav_opd_k, coalesce(oeav_opd_n, '') as oeav_opd_n,"
					" coalesce(oat.oeav_va_id, 0) as oeav_vid1, coalesce(oat.oeav_va_k, '') as oeav_vk1, coalesce(oat.oeav_va_n, '') as oeav_vn1,"
					" coalesce(oeav_opd_avt1, '0') as oeav_opd_avt1,"
					" coalesce(oat1.oeav_va_id, 0) as oeav_vid2, coalesce(oat1.oeav_va_k, '') as oeav_vk2, coalesce(oat1.oeav_va_n, '') as oeav_vn2,"
					" coalesce(oeav_opd_avt2, '0') as oeav_opd_avt2,"
					" coalesce(oat2.oeav_va_id, 0) as oeav_vid3, coalesce(oat2.oeav_va_k, '') as oeav_vk3, coalesce(oat2.oeav_va_n, '') as oeav_vn3,"
					" coalesce(oeav_opd_avt3, '0') as oeav_opd_avt3,"
					" coalesce(oeav_txo_k, '') as oeav_txo_k, "
					" coalesce(a.oeav_ps_id, 0) as oeav_sid1, coalesce(a.oeav_ps_n, '') as oeav_sn1, coalesce(a.oeav_ps_s, '') as oeav_sk1, coalesce(a.oeav_ps_typ, '0') as oeav_styp1,"
					" coalesce(oat3.oeav_va_id, 0) as oeav_vid4, coalesce(oat3.oeav_va_k, '') as oeav_vk4, coalesce(oat3.oeav_va_n, '') as oeav_vn4,"
					" coalesce(oat4.oeav_va_id, 0) as oeav_vid5, coalesce(oat4.oeav_va_k, '') as oeav_vk5, coalesce(oat4.oeav_va_n, '') as oeav_vn5,"
					" coalesce(a1.oeav_ps_id, 0) as oeav_sid2, coalesce(a1.oeav_ps_n, '') as oeav_sn2, coalesce(a1.oeav_ps_s, '') as oeav_sk2, coalesce(a1.oeav_ps_typ, '0') as oeav_styp2,"
					" coalesce(oat5.oeav_va_id, 0) as oeav_vid6, coalesce(oat5.oeav_va_k, '') as oeav_vk6, coalesce(oat5.oeav_va_n, '') as oeav_vn6,"
					" coalesce(oat6.oeav_va_id, 0) as oeav_vid7, coalesce(oat6.oeav_va_k, '') as oeav_vk7, coalesce(oat6.oeav_va_n, '') as oeav_vn7"

					" from oeav_txo top"
					" left join oeav_opd pd on top.oeav_txo_dokk = pd.oeav_opd_id"
					" left join oeav_va oat on pd.oeav_opd_av1 = oat.oeav_va_id"
					" left join oeav_va oat1 on pd.oeav_opd_av2 = oat1.oeav_va_id"
					" left join oeav_va oat2 on pd.oeav_opd_av3 = oat2.oeav_va_id"
					" left join oeav_ps a on top.oeav_txo_db = a.oeav_ps_id"
					" left join oeav_va oat3 on a.oeav_ps_av1 = oat3.oeav_va_id"
					" left join oeav_va oat4 on a.oeav_ps_av1 = oat4.oeav_va_id"
					" left join oeav_ps a1 on top.oeav_txo_kr = a1.oeav_ps_id"
					" left join oeav_va oat5 on a1.oeav_ps_av1 = oat5.oeav_va_id"
					" left join oeav_va oat6 on a1.oeav_ps_av1 = oat6.oeav_va_id"
					" where oeav_txo_dokk = '" + std::to_string(docId) + "'"
					" order by oeav_txo_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<TypicalOperationList> tOpList = boost::make_shared<TypicalOperationList>();

	for (auto row : *result)
	{
		tOpList->emplace_back(TypicalOperation(row.at("oeav_txo_id").as<int>(),
			PrimaryDocument(row.at("oeav_opd_id").as<int>(), row.at("oeav_opd_k").c_str(),
				row.at("oeav_opd_n").c_str(),
				AnalyticalType(row.at("oeav_vid1").as<int>(), row.at("oeav_vk1").c_str(), row.at("oeav_vn1").c_str()),
				AccountTypes(row.at("oeav_opd_avt1").as<int>()),
				AnalyticalType(row.at("oeav_vid2").as<int>(), row.at("oeav_vk2").c_str(), row.at("oeav_vn2").c_str()),
				AccountTypes(row.at("oeav_opd_avt2").as<int>()),
				AnalyticalType(row.at("oeav_vid3").as<int>(), row.at("oeav_vk3").c_str(), row.at("oeav_vn3").c_str()),
				AccountTypes(row.at("oeav_opd_avt3").as<int>())),
			row.at("oeav_txo_k").c_str(),
			Account(row.at("oeav_sid1").as<int>(), row.at("oeav_sn1").c_str(), row.at("oeav_sk1").c_str(), AccountTypes(row.at("oeav_styp1").as<int>()),
				AnalyticalType(row.at("oeav_vid4").as<int>(), row.at("oeav_vk4").c_str(), row.at("oeav_vn4").c_str()),
				AnalyticalType(row.at("oeav_vid5").as<int>(), row.at("oeav_vk5").c_str(), row.at("oeav_vn5").c_str())),
			Account(row.at("oeav_sid2").as<int>(), row.at("oeav_sn2").c_str(), row.at("oeav_sk2").c_str(), AccountTypes(row.at("oeav_styp2").as<int>()),
				AnalyticalType(row.at("oeav_vid6").as<int>(), row.at("oeav_vk6").c_str(), row.at("oeav_vn6").c_str()),
				AnalyticalType(row.at("oeav_vid7").as<int>(), row.at("oeav_vk7").c_str(), row.at("oeav_vn7").c_str()))
		));
	}

	return tOpList;
}

void CardfilesRepository::updateTypicalOperation(int id, int docId, const std::string &name, int debetId, int creditId) const
{
	std::string sql{ "update oeav_txo set oeav_txo_k = '" + name + "'" };
	if (docId && docId != 0)
		sql += " , oeav_txo_dokk = '" + std::to_string(docId) + "'";
	if (debetId && debetId != 0)
		sql += " , oeav_txo_db = '" + std::to_string(debetId) + "'";
	if (creditId && creditId != 0)
		sql += " , oeav_txo_kr = '" + std::to_string(creditId) + "'";
	sql += " where oeav_txo_id = '" + std::to_string(id) + "'";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::addTypicalOperation(int docId, const std::string &name, int debetIt, int creditId) const
{
	std::string sql{ "insert into oeav_txo(oeav_txo_dokk, oeav_txo_k, oeav_txo_db, oeav_txo_kr)"
		" values('" + std::to_string(docId) + "', '" + name + "', '" + std::to_string(debetIt) + "', '"
		+ std::to_string(creditId) + "')" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::deleteTypicalOperation(int id) const
{
	std::string sql{ "delete from oeav_txo where oeav_txo_id = '" + std::to_string(id) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

int CardfilesRepository::findAccIdByContent(const std::string &code, const std::string &name) const
{
	std::string sql{ "select oeav_ps_id from oeav_ps where oeav_ps_s = '" + code + "' and oeav_ps_n = '" + name + "'" };

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
	std::string sql{ "select oeav_opd_id from oeav_opd where oeav_opd_k = '" + code + "' and oeav_opd_n = '" + name + "'" };

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
	std::string sql{ "SELECT * FROM oeav_kau OAAC INNER JOIN oeav_va OAT"
		" ON OAAC.oeav_kau_v = OAT.oeav_va_id where oeav_kau_id = '" + std::to_string(atId) + "' ORDER BY oeav_kau_id" };

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
	std::string sql{ "SELECT * FROM oeav_kau OAAC INNER JOIN oeav_va OAT"
		" ON OAAC.oeav_kau_v = OAT.oeav_va_id where oeav_kau_v = '" + std::to_string(atId) + "' ORDER BY oeav_kau_id" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AnalyticalAccountingCodeList> analytCodesList = boost::make_shared<AnalyticalAccountingCodeList>();

	for (auto row : *result)
		analytCodesList->emplace_back(AnalyticalAccountingCode(row[0].as<int>(), 0, AnalyticalType(row[4].as<int>(), row[5].c_str(),
			row[6].c_str()), row[3].c_str()));

	return analytCodesList;
}

std::vector<std::tuple<std::string, std::string>> CardfilesRepository::getAccountsFromAccBook() const
{
	std::string sql{ "select distinct coalesce(oeav_ks_s, 0) as oeav_ks_s, coalesce(oeav_ks_sn, '') as oeav_ks_sn from oeav_ks" };

	std::vector<std::tuple<std::string, std::string>> accounts;

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	for (auto row : *result)
		accounts.emplace_back(std::make_tuple(row.at("oeav_ks_s").c_str(), row.at("oeav_ks_sn").c_str()));

	return accounts;
}