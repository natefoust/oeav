#pragma once

#include "connection.h"

#include <boost/make_shared.hpp>

using namespace oeav::domain;
using namespace pqxx;

boost::shared_ptr<pqxx::result> Connection::execute(const std::string &sql) const
{
	try
	{
		pqxx::connection connection("host=localhost port=5432 dbname=oeav user=postgres password=123");
		pqxx::work worker(connection);

		pqxx::result result = worker.exec(sql);
		worker.commit();

		boost::shared_ptr<pqxx::result> resultPtr = boost::make_shared<pqxx::result>(result);

		return resultPtr;
	}
	catch (...)
	{
		// это плохо :(
	}
}