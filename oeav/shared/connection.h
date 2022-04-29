#pragma once

#include "iconnection.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace oeav
{
	namespace domain
	{
		class Connection : public IConnection
		{
		public:
			boost::shared_ptr<pqxx::result> execute(const std::string &sql) const override;
			void createConnection() override;

		private:
			boost::shared_ptr<pqxx::connection> _connection = 
				boost::make_shared<pqxx::connection>("host=localhost port=5432 dbname=oeav user=postgres password=123 client_encoding=WIN1251");
		};
	}
}