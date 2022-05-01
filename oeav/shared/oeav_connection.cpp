#pragma once
#include <iostream>
#include "oeav_connection.h"

#include <boost/make_shared.hpp>

using namespace oeav::domain;
using namespace pqxx;

boost::shared_ptr<pqxx::result> Connection::execute(const std::string &sql) const
{
	try
	{
		//pqxx::connection connection("host=localhost port=5432 dbname=oeav user=postgres password=123 client_encoding=WIN1251");
			
		pqxx::work worker(*_connection);

		pqxx::result result = worker.exec(sql);
		worker.commit();

		boost::shared_ptr<pqxx::result> resultPtr = boost::make_shared<pqxx::result>(result);

		return resultPtr;
	}
	catch (pqxx::sql_error const &e)
	{
		std::string a{ e.what() };
		std::string b{ e.query() };
	}
}

void Connection::createConnection()
{

}