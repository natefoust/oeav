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
	std::string sql{ "SELECT oeav_aid, oeav_a0, coalesce(oeav_av, 0) as oeav_av, coalesce(oeav_ak, '') as oeav_ak,"
		" coalesce(oeav_vid, 0) as oeav_vid, coalesce(oeav_vk, '') as oeav_vk, coalesce(oeav_vn, '') as oeav_vn"
		" FROM oeav_a OAAC INNER JOIN oeav_v OAT"
		" ON OAAC.OEAV_av = OAT.oeav_vid ORDER BY oeav_aid" };

	boost::shared_ptr<result> result = 
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AnalyticalAccountingCodeList> analytCodesList = boost::make_shared<AnalyticalAccountingCodeList>();

	for (auto row : *result)
		analytCodesList->emplace_back(AnalyticalAccountingCode(row.at("oeav_aid").as<int>(), row.at("oeav_a0").as<int>(), 
			AnalyticalType(row.at("oeav_vid").as<int>(), row.at("oeav_vk").c_str(),
			row.at("oeav_vn").c_str()), row.at("oeav_ak").c_str()));

	return analytCodesList;
}

void CardfilesRepository::addAnalyticalAccountingCode(const std::string &analyticalCode, int typeId) const
{
	if (typeId == 0)
	{
		std::string idSql = "SELECT oeav_vid from oeav_v order by oeav_vid desc limit 1";
		
		boost::shared_ptr<result> resultId =
			InstanceFactory<IConnection>::getInstance()->execute(idSql);

		if (resultId->empty())
			return;

		auto row = resultId->at(0);
		typeId = row[0].as<int>();
	}

		std::string sql{};
	
	sql += "INSERT INTO oeav_a(oeav_ak, oeav_av) VALUES('" + analyticalCode
		+ "', " + std::to_string(typeId) + ")";

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::addAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const
{
	std::string sql{};

	sql += "INSERT INTO oeav_v(oeav_vk, oeav_vn) VALUES('" + analyticalCode
		+ "', '" + analyticalName + "')";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

boost::shared_ptr<AnalyticalTypeList> CardfilesRepository::getAnalyticalTypes() const
{
	std::string sql{ "SELECT oeav_vid, oeav_v0, coalesce(oeav_vk, '') as oeav_vk, coalesce(oeav_vn, '') as oeav_vn"
					 " FROM oeav_v ORDER BY oeav_vid" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AnalyticalTypeList> analytList = boost::make_shared<AnalyticalTypeList>();

	for (auto row : *result)
		analytList->emplace_back(AnalyticalType(row.at("oeav_vid").as<int>(), row.at("oeav_vk").c_str(), row.at("oeav_vn").c_str()));

	return analytList;
}

void CardfilesRepository::deleteAnalyticalType(int id) const
{
	std::string sql{ "DELETE FROM oeav_v WHERE oeav_vid = '" + std::to_string(id) +  "'" };
	
	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::updateAnalyticalType(int id, const std::string &analyticalCode, const std::string &analyticalName) const
{
	std::string sql{ "UPDATE oeav_v SET oeav_vk = '" + analyticalCode + "', oeav_vn = '" + analyticalName
		+ "' WHERE oeav_vid= '" + std::to_string(id) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::deleteAnalyticalAccountCode(int typeId) const
{
	std::string sql{ "DELETE FROM oeav_a WHERE oeav_aid = '" + std::to_string(typeId) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::updateAnalyticalAccountCode(int itemId, int typeId, const std::string &analyticalCode) const
{
	std::string sql{ "UPDATE oeav_a SET oeav_av = '" + std::to_string(typeId) + "',"
		" oeav_ak = '" + analyticalCode + "' WHERE oeav_aid = '" + std::to_string(itemId) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

boost::shared_ptr<AccountList> CardfilesRepository::getAccounts() const
{
	std::string sql{ "select oeav_sid, oeav_s0, coalesce(oeav_sk, '') as oeav_sk, coalesce(oeav_sn, '') as oeav_sn , coalesce(oeav_styp, '0') as oeav_styp , coalesce(oat.oeav_vid, 0) as id1, coalesce(oat.oeav_vk, '') as code1, coalesce(oat.oeav_vn, '') as name1 ,"
		" coalesce(oat2.oeav_vid, 0) as id2, coalesce(oat2.oeav_vk, '') as code2, coalesce(oat2.oeav_vn, '') as name2 from oeav_s as oa"
		" left join oeav_v oat on oa.oeav_sav1 = oat.oeav_vid"
		" left join oeav_v oat2 on oa.oeav_sav2 = oat2.oeav_vid"
		" order by oeav_sid" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AccountList> accountList = boost::make_shared<AccountList>();
	
	for (auto row : *result)
	{
		std::stringstream ss;
		ss << row.at("oeav_sid").as<int>();
		ss << row.at("id1").as<int>();

		accountList->emplace_back(Account(row.at("oeav_sid").as<int>(), row.at("oeav_sn").c_str(), row.at("oeav_sk").c_str(),
		AccountTypes(row.at("oeav_styp").as<int>()),
		AnalyticalType(row.at("id1").as<int>(), row.at("code1").c_str(), row.at("name1").c_str()),
		AnalyticalType(row.at("id2").as<int>(), row.at("code2").c_str(), row.at("name2").c_str())));
	}
		
	return accountList;
}

int CardfilesRepository::findIdByContent(const std::string &code, const std::string &name) const
{
	std::string sql{ "select oeav_vid from oeav_v where oeav_vk = '" + code + "' and oeav_vn = '" + name + "'" };

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
	std::string sql{ "update oeav_s set oeav_sk = '" + code + "',"
		" oeav_sn = '" + name + "'" };
	if (typeId && typeId != 0)
		sql += ", oeav_styp = '" + std::to_string(typeId) + "'";
	if (analyt1Id && analyt1Id != 0)
		sql += ", oeav_sav1 = '" + std::to_string(analyt1Id) + "'";
	if (analyt2Id && analyt2Id != 0)
		sql += ", oeav_sav2 = '" + std::to_string(analyt2Id) + "'";
	sql += " where oeav_sid = '" + std::to_string(id) + "'";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::addAccount(const std::string &code, const std::string &name,
	int typeId, int analyt1Id, int analyt2Id) const
{
	std::string sql{ "insert into oeav_s(oeav_sk, oeav_sn, oeav_styp, oeav_sav1,"
		" oeav_sav2) values('" + code + "', '" + name + "', '" + std::to_string(typeId) + "', '" 
		+ std::to_string(analyt1Id) + "', '" + std::to_string(analyt2Id) + "')" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::deleteAccount(int id) const
{
	std::string sql{ "delete from oeav_s where oeav_sid = '" + std::to_string(id) + "'" };
	
	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

boost::shared_ptr<PrimaryDocumentList> CardfilesRepository::getPrimaryDocuments() const
{
	std::string sql{ "select oeav_did, coalesce(oeav_dk, '') as oeav_dk, coalesce(oeav_dn, '') as oeav_dn, "
			" coalesce(oat.oeav_vid, 0) as oeav_vid1, coalesce(oat.oeav_vk, '') as oeav_vk1, coalesce(oat.oeav_vn, '') as oeav_vn1,"
			" coalesce(oeav_davt1, '0') as oeav_davt1, "
			" coalesce(oat1.oeav_vid, 0) as oeav_vid2, coalesce(oat1.oeav_vk, '') as oeav_vk2, coalesce(oat1.oeav_vn, '') as oeav_vn2,"
			" coalesce(oeav_davt2, '0') as oeav_davt2, "
			" coalesce(oat2.oeav_vid, 0) as oeav_vid3, coalesce(oat2.oeav_vk, '') as oeav_vk3, coalesce(oat2.oeav_vn, '') as oeav_vn3,"
			" coalesce(oeav_davt3, '0') as oeav_davt3 "
			" from oeav_d pd"
			" left join oeav_v oat on pd.oeav_dav1 = oat.oeav_vid"
			" left join oeav_v oat1 on pd.oeav_dav2 = oat1.oeav_vid"
			" left join oeav_v oat2 on pd.oeav_dav3 = oat2.oeav_vid"
			" order by oeav_did" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<PrimaryDocumentList> pDocList = boost::make_shared<PrimaryDocumentList>();

	for (auto row : *result)
	{
		pDocList->emplace_back(PrimaryDocument(row.at("oeav_did").as<int>(), row.at("oeav_dk").c_str(), row.at("oeav_dn").c_str(),
			AnalyticalType(row.at("oeav_vid1").as<int>(), row.at("oeav_vk1").c_str(), row.at("oeav_vn1").c_str()), AccountTypes(row.at("oeav_davt1").as<int>()),
			AnalyticalType(row.at("oeav_vid2").as<int>(), row.at("oeav_vk2").c_str(), row.at("oeav_vn2").c_str()), AccountTypes(row.at("oeav_davt2").as<int>()),
			AnalyticalType(row.at("oeav_vid3").as<int>(), row.at("oeav_vk3").c_str(), row.at("oeav_vn3").c_str()), AccountTypes(row.at("oeav_davt3").as<int>())
		));
	}

	return pDocList;
}

boost::shared_ptr<PrimaryDocument> CardfilesRepository::getPrimaryDocument(int docId) const
{
	std::string sql{ "select oeav_did, coalesce(oeav_dk, '') as oeav_dk, coalesce(oeav_dn, '') as oeav_dn, "
			" coalesce(oat.oeav_vid, 0) as oeav_vid1, coalesce(oat.oeav_vk, '') as oeav_vk1, coalesce(oat.oeav_vn, '') as oeav_vn1,"
			" coalesce(oeav_davt1, '0') as oeav_davt1, "
			" coalesce(oat1.oeav_vid, 0) as oeav_vid2, coalesce(oat1.oeav_vk, '') as oeav_vk2, coalesce(oat1.oeav_vn, '') as oeav_vn2,"
			" coalesce(oeav_davt2, '0') as oeav_davt2, "
			" coalesce(oat2.oeav_vid, 0) as oeav_vid3, coalesce(oat2.oeav_vk, '') as oeav_vk3, coalesce(oat2.oeav_vn, '') as oeav_vn3,"
			" coalesce(oeav_davt3, '0') as oeav_davt3 "
			" from oeav_d pd"
			" left join oeav_v oat on pd.oeav_dav1 = oat.oeav_vid"
			" left join oeav_v oat1 on pd.oeav_dav2 = oat1.oeav_vid"
			" left join oeav_v oat2 on pd.oeav_dav3 = oat2.oeav_vid"
			" where oeav_did = '" + std::to_string(docId) + "'"
			" order by oeav_did" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<PrimaryDocument> pDoc = boost::make_shared<PrimaryDocument>();

	for (auto row : *result)
	{
		pDoc = boost::make_shared<PrimaryDocument>(PrimaryDocument(row.at("oeav_did").as<int>(), row.at("oeav_dk").c_str(), row.at("oeav_dn").c_str(),
			AnalyticalType(row.at("oeav_vid1").as<int>(), row.at("oeav_vk1").c_str(), row.at("oeav_vn1").c_str()), AccountTypes(row.at("oeav_davt1").as<int>()),
			AnalyticalType(row.at("oeav_vid2").as<int>(), row.at("oeav_vk2").c_str(), row.at("oeav_vn2").c_str()), AccountTypes(row.at("oeav_davt2").as<int>()),
			AnalyticalType(row.at("oeav_vid3").as<int>(), row.at("oeav_vk3").c_str(), row.at("oeav_vn3").c_str()), AccountTypes(row.at("oeav_davt3").as<int>())
		));
	}

	return pDoc;
}

void CardfilesRepository::updatePrimaryDocument(int id, const std::string &code, const std::string &name, int analyt1,
	int type1, int analyt2, int type2, int analyt3, int type3) const
{
	std::string sql{ "update oeav_d set oeav_dk = '" + code + "',"
		" oeav_dn = '" + name + "'" };
	if (analyt1 && analyt1 != 0)
		sql += ", oeav_dav1 = '" + std::to_string(analyt1) + "'";
	if (type1 && type1 != 0)
		sql += ", oeav_davt1 = '" + std::to_string(type1) + "'";
	if (analyt2 && analyt2 != 0)
		sql += ", oeav_dav2 = '" + std::to_string(analyt2) + "'";
	if (type2 && type2 != 0)
		sql += ", oeav_davt2 = '" + std::to_string(type2) + "'";
	if (analyt3 && analyt3 != 0)
		sql += ", oeav_dav3 = '" + std::to_string(analyt3) + "'";
	if (type3 && type3 != 0)
		sql += ", oeav_davt3 = '" + std::to_string(type3) + "'";
	sql += " where oeav_did = '" + std::to_string(id) + "'";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::addPrimaryDocument(const std::string &code, const std::string &name, int analyt1,
	int type1, int analyt2, int type2, int analyt3, int type3) const
{
	std::string sql{ "insert into oeav_d(oeav_dk, oeav_dn, oeav_dav1, oeav_davt1, oeav_dav2, oeav_davt2, oeav_dav3, oeav_davt3)"
		" values('" + code + "', '" + name + "', '" + std::to_string(analyt1) + "', '"
		+ std::to_string(type1) + "', '" + std::to_string(analyt2) + "', '" + std::to_string(type2) + 
		"', '" + std::to_string(analyt3) + "', '" + std::to_string(type3) + "')" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::deletePrimaryDocument(int id) const
{
	std::string sql{ "delete from oeav_d where oeav_did = '" + std::to_string(id) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

boost::shared_ptr<TypicalOperationList> CardfilesRepository::getTypicalOperations() const
{
	std::string sql{ "select oeav_oid, oeav_o0, coalesce(oeav_did, 0) as oeav_did, coalesce(oeav_dk, '') as oeav_dk, coalesce(oeav_dn, '') as oeav_dn,"
					" coalesce(oat.oeav_vid, 0) as oeav_vid1, coalesce(oat.oeav_vk, '') as oeav_vk1, coalesce(oat.oeav_vn, '') as oeav_vn1,"
					" coalesce(oeav_davt1, '0') as oeav_davt1,"
					" coalesce(oat1.oeav_vid, 0) as oeav_vid2, coalesce(oat1.oeav_vk, '') as oeav_vk2, coalesce(oat1.oeav_vn, '') as oeav_vn2,"
					" coalesce(oeav_davt2, '0') as oeav_davt2,"
					" coalesce(oat2.oeav_vid, 0) as oeav_vid3, coalesce(oat2.oeav_vk, '') as oeav_vk3, coalesce(oat2.oeav_vn, '') as oeav_vn3,"
					" coalesce(oeav_davt3, '0') as oeav_davt3,"
					" coalesce(oeav_ok, '') as oeav_ok, "
					" coalesce(a.oeav_sid, 0) as oeav_sid1, coalesce(a.oeav_sn, '') as oeav_sn1, coalesce(a.oeav_sk, '') as oeav_sk1, coalesce(a.oeav_styp, '0') as oeav_styp1,"
					" coalesce(oat3.oeav_vid, 0) as oeav_vid4, coalesce(oat3.oeav_vk, '') as oeav_vk4, coalesce(oat3.oeav_vn, '') as oeav_vn4,"
					" coalesce(oat4.oeav_vid, 0) as oeav_vid5, coalesce(oat4.oeav_vk, '') as oeav_vk5, coalesce(oat4.oeav_vn, '') as oeav_vn5,"
					" coalesce(a1.oeav_sid, 0) as oeav_sid2, coalesce(a.oeav_sn, '') as oeav_sn2, coalesce(a1.oeav_sk, '') as oeav_sk2, coalesce(a1.oeav_styp, '0') as oeav_styp2,"
					" coalesce(oat5.oeav_vid, 0) as oeav_vid6, coalesce(oat5.oeav_vk, '') as oeav_vk6, coalesce(oat5.oeav_vn, '') as oeav_vn6,"
					" coalesce(oat6.oeav_vid, 0) as oeav_vid7, coalesce(oat6.oeav_vk, '') as oeav_vk7, coalesce(oat6.oeav_vn, '') as oeav_vn7"
		
					" from oeav_o top"
					" left join oeav_d pd on top.oeav_odok = pd.oeav_did"
					" left join oeav_v oat on pd.oeav_dav1 = oat.oeav_vid"
					" left join oeav_v oat1 on pd.oeav_dav2 = oat1.oeav_vid"
					" left join oeav_v oat2 on pd.oeav_dav3 = oat2.oeav_vid"
					" left join oeav_s a on top.oeav_odb = a.oeav_sid"
					" left join oeav_v oat3 on a.oeav_sav1 = oat3.oeav_vid"
					" left join oeav_v oat4 on a.oeav_sav1 = oat4.oeav_vid"
					" left join oeav_s a1 on top.oeav_okr = a1.oeav_sid"
					" left join oeav_v oat5 on a1.oeav_sav1 = oat5.oeav_vid"
					" left join oeav_v oat6 on a1.oeav_sav1 = oat6.oeav_vid"
					" order by oeav_oid" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<TypicalOperationList> tOpList = boost::make_shared<TypicalOperationList>();

	
	for (auto row : *result)
	{
		tOpList->emplace_back(TypicalOperation(row.at("oeav_oid").as<int>(),
			PrimaryDocument(row.at("oeav_did").as<int>(), row.at("oeav_dk").c_str(),
				row.at("oeav_dn").c_str(), 
				AnalyticalType(row.at("oeav_vid1").as<int>(), row.at("oeav_vk1").c_str(), row.at("oeav_vn1").c_str()), 
				AccountTypes(row.at("oeav_davt1").as<int>()), 
				AnalyticalType(row.at("oeav_vid2").as<int>(), row.at("oeav_vk2").c_str(), row.at("oeav_vn2").c_str()),
				AccountTypes(row.at("oeav_davt2").as<int>()),
				AnalyticalType(row.at("oeav_vid3").as<int>(), row.at("oeav_vk3").c_str(), row.at("oeav_vn3").c_str()),
				AccountTypes(row.at("oeav_davt3").as<int>())),
			row.at("oeav_ok").c_str(),
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
	std::string sql{ "select oeav_oid, oeav_o0, coalesce(oeav_did, 0) as oeav_did, coalesce(oeav_dk, '') as oeav_dk, coalesce(oeav_dn, '') as oeav_dn,"
					" coalesce(oat.oeav_vid, 0) as oeav_vid1, coalesce(oat.oeav_vk, '') as oeav_vk1, coalesce(oat.oeav_vn, '') as oeav_vn1,"
					" coalesce(oeav_davt1, '0') as oeav_davt1,"
					" coalesce(oat1.oeav_vid, 0) as oeav_vid2, coalesce(oat1.oeav_vk, '') as oeav_vk2, coalesce(oat1.oeav_vn, '') as oeav_vn2,"
					" coalesce(oeav_davt2, '0') as oeav_davt2,"
					" coalesce(oat2.oeav_vid, 0) as oeav_vid3, coalesce(oat2.oeav_vk, '') as oeav_vk3, coalesce(oat2.oeav_vn, '') as oeav_vn3,"
					" coalesce(oeav_davt3, '0') as oeav_davt3,"
					" coalesce(oeav_ok, '') as oeav_ok, "
					" coalesce(a.oeav_sid, 0) as oeav_sid1, coalesce(a.oeav_sn, '') as oeav_sn1, coalesce(a.oeav_sk, '') as oeav_sk1, coalesce(a.oeav_styp, '0') as oeav_styp1,"
					" coalesce(oat3.oeav_vid, 0) as oeav_vid4, coalesce(oat3.oeav_vk, '') as oeav_vk4, coalesce(oat3.oeav_vn, '') as oeav_vn4,"
					" coalesce(oat4.oeav_vid, 0) as oeav_vid5, coalesce(oat4.oeav_vk, '') as oeav_vk5, coalesce(oat4.oeav_vn, '') as oeav_vn5,"
					" coalesce(a1.oeav_sid, 0) as oeav_sid2, coalesce(a.oeav_sn, '') as oeav_sn2, coalesce(a1.oeav_sk, '') as oeav_sk2, coalesce(a1.oeav_styp, '0') as oeav_styp2,"
					" coalesce(oat5.oeav_vid, 0) as oeav_vid6, coalesce(oat5.oeav_vk, '') as oeav_vk6, coalesce(oat5.oeav_vn, '') as oeav_vn6,"
					" coalesce(oat6.oeav_vid, 0) as oeav_vid7, coalesce(oat6.oeav_vk, '') as oeav_vk7, coalesce(oat6.oeav_vn, '') as oeav_vn7"

					" from oeav_o top"
					" left join oeav_d pd on top.oeav_odok = pd.oeav_did"
					" left join oeav_v oat on pd.oeav_dav1 = oat.oeav_vid"
					" left join oeav_v oat1 on pd.oeav_dav2 = oat1.oeav_vid"
					" left join oeav_v oat2 on pd.oeav_dav3 = oat2.oeav_vid"
					" left join oeav_s a on top.oeav_odb = a.oeav_sid"
					" left join oeav_v oat3 on a.oeav_sav1 = oat3.oeav_vid"
					" left join oeav_v oat4 on a.oeav_sav1 = oat4.oeav_vid"
					" left join oeav_s a1 on top.oeav_okr = a1.oeav_sid"
					" left join oeav_v oat5 on a1.oeav_sav1 = oat5.oeav_vid"
					" left join oeav_v oat6 on a1.oeav_sav1 = oat6.oeav_vid"
					" where oeav_odok = '" + std::to_string(docId) + "'"
					" order by oeav_oid" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<TypicalOperationList> tOpList = boost::make_shared<TypicalOperationList>();

	for (auto row : *result)
	{
		tOpList->emplace_back(TypicalOperation(row.at("oeav_oid").as<int>(),
			PrimaryDocument(row.at("oeav_did").as<int>(), row.at("oeav_dk").c_str(),
				row.at("oeav_dn").c_str(),
				AnalyticalType(row.at("oeav_vid1").as<int>(), row.at("oeav_vk1").c_str(), row.at("oeav_vn1").c_str()),
				AccountTypes(row.at("oeav_davt1").as<int>()),
				AnalyticalType(row.at("oeav_vid2").as<int>(), row.at("oeav_vk2").c_str(), row.at("oeav_vn2").c_str()),
				AccountTypes(row.at("oeav_davt2").as<int>()),
				AnalyticalType(row.at("oeav_vid3").as<int>(), row.at("oeav_vk3").c_str(), row.at("oeav_vn3").c_str()),
				AccountTypes(row.at("oeav_davt3").as<int>())),
			row.at("oeav_ok").c_str(),
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
	std::string sql{ "update oeav_o set oeav_ok = '" + name + "'" };
	if (docId && docId != 0)
		sql += " , oeav_odok = '" + std::to_string(docId) + "'";
	if (debetId && debetId != 0)
		sql += " , oeav_odb = '" + std::to_string(debetId) + "'";
	if (creditId && creditId != 0)
		sql += " , oeav_okr = '" + std::to_string(creditId) + "'";
	sql += " where oeav_oid = '" + std::to_string(id) + "'";

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::addTypicalOperation(int docId, const std::string &name, int debetIt, int creditId) const
{
	std::string sql{ "insert into oeav_o(oeav_odok, oeav_ok, oeav_odb, oeav_okr)"
		" values('" + std::to_string(docId) + "', '" + name + "', '" + std::to_string(debetIt) + "', '"
		+ std::to_string(creditId) + "')" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::deleteTypicalOperation(int id) const
{
	std::string sql{ "delete from oeav_o where oeav_oid = '" + std::to_string(id) + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

int CardfilesRepository::findAccIdByContent(const std::string &code, const std::string &name) const
{
	std::string sql{ "select oeav_sid from oeav_s where oeav_sk = '" + code + "' and oeav_sn = '" + name + "'" };

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
	std::string sql{ "select oeav_did from oeav_d where oeav_dk = '" + code + "' and oeav_dn = '" + name + "'" };

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
	std::string sql{ "SELECT * FROM oeav_a OAAC INNER JOIN oeav_v OAT"
		" ON OAAC.oeav_av = OAT.oeav_vid where oeav_aid = '" + std::to_string(atId) + "' ORDER BY oeav_aid" };

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
	std::string sql{ "SELECT * FROM oeav_a OAAC INNER JOIN oeav_v OAT"
		" ON OAAC.oeav_av = OAT.oeav_vid where oeav_av = '" + std::to_string(atId) + "' ORDER BY oeav_aid" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AnalyticalAccountingCodeList> analytCodesList = boost::make_shared<AnalyticalAccountingCodeList>();

	for (auto row : *result)
		analytCodesList->emplace_back(AnalyticalAccountingCode(row[0].as<int>(), 0, AnalyticalType(row[4].as<int>(), row[5].c_str(),
			row[6].c_str()), row[3].c_str()));

	return analytCodesList;
}