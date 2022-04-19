#pragma once

#include "icardfiles_repository.h"

namespace oeav
{
	namespace domain
	{
		class CardfilesRepository : public ICardfilesRepository
		{
		public:
			boost::shared_ptr<AnalyticalAccountingCodeList> getAnalyticalAccountingCodes() const override;
		};
	}
}