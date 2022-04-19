#pragma once

#include "iconnection.h"

namespace oeav
{
	namespace domain
	{
		class Connection : public IConnection
		{
			boost::shared_ptr<pqxx::result> execute(const std::string &sql) const override;
		};
	}
}