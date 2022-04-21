#pragma once

#include "cardfiles_repository.h"

#include <sstream>
#include <pqxx/pqxx>

#include "../shared/iconnection.h"
#include "../shared/instance_factory.h"

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

void CardfilesRepository::addAnalyticalAccountingCode(std::string analyticalCode, int typeId) const
{
	std::string sql{};
	
	sql += "INSERT INTO OEAV_ANALYTICAL_ACCOUNTING_CODES(oeav_analytical_code, oeav_analytical_type) VALUES('" + analyticalCode
		+ "', " + std::to_string(typeId) + ")";

	boost::shared_ptr<result> result =
		InstanceFactory<IConnection>::getInstance()->execute(sql);
}