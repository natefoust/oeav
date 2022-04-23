#pragma once

#include "cardfiles_repository.h"

#include <boost/make_shared.hpp>
#include <pqxx/pqxx>

#include "../shared/iconnection.h"
#include "../shared/instance_factory.h"

#include "../domain/analytical_type.h"

using namespace oeav::domain;
using namespace pqxx;

boost::shared_ptr<AnalyticalAccountingCodeList> CardfilesRepository::getAnalyticalAccountingCodes() const
{
	std::string sql{ "SELECT * FROM OEAV_ANALYTICAL_ACCOUNTING_CODES" };

	boost::shared_ptr<result> result = 
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	std::stringstream s;
	for (auto row : *result)
		s << row[0].c_str() << '\n';

}

void CardfilesRepository::addAnalyticalAccountingCode(const std::string &analyticalCode, int typeId) const
{
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
	std::string sql{ "SELECT * FROM OEAV_ANALYTICAL_TYPES" };

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);

	boost::shared_ptr<AnalyticalTypeList> analytList = boost::make_shared<AnalyticalTypeList>();

	for (auto row : *result)
		analytList->emplace_back(AnalyticalType(row[0].as<int>(), row[1].c_str(), row[2].c_str()));

	return analytList;
}

void CardfilesRepository::deleteAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const
{
	std::string sql{ "DELETE FROM OEAV_ANALYTICAL_TYPES WHERE OEAV_AT_CODE = '" + analyticalCode + "' AND OEAV_AT_NAME = '" + analyticalName + "'" };
	
	InstanceFactory<IConnection>::getInstance()->execute(sql);
}

void CardfilesRepository::updateAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName,
	const std::string &analyticalCodeP, const std::string &analyticalNameP) const
{
	std::string sql{ "UPDATE OEAV_ANALYTICAL_TYPES SET oeav_at_code = '" + analyticalCode + "', oeav_at_name = '" + analyticalName
		+ "' WHERE oeav_at_code = '" + analyticalCodeP + "' AND oeav_at_name = '" + analyticalNameP + "'" };

	InstanceFactory<IConnection>::getInstance()->execute(sql);
}