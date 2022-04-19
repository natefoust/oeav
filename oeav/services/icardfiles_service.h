#pragma once

// boost
#include <boost/shared_ptr.hpp>

#include "../domain/analytical_accounting_code.h"

namespace oeav
{
	namespace domain
	{
		class AnalyticalAccountingCodeList;
	}

	namespace service
	{
		class ICardfilesService
		{
		public:
			virtual boost::shared_ptr<domain::AnalyticalAccountingCodeList> getAnalyticalAccountingCodes() const = 0;
		};
	}
}
