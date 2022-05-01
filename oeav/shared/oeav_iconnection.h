#pragma once

#include <pqxx/pqxx>
#include <boost/shared_ptr.hpp>

namespace oeav
{
	namespace domain
	{
		class IConnection
		{
		public:
			virtual boost::shared_ptr<pqxx::result> execute(const std::string &sql) const = 0;
			virtual void createConnection() = 0;
		};
	}
}