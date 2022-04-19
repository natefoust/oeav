#pragma once

#include <boost/shared_ptr.hpp>

namespace oeav
{
	namespace domain
	{
		class AnalyticalAccountingCodeList;

		class ICardfilesRepository
		{
		public:
			virtual boost::shared_ptr<AnalyticalAccountingCodeList> getAnalyticalAccountingCodes() const = 0;
		};
	}
}