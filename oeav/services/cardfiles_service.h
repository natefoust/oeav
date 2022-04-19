#pragma once

// it's own interface
#include "../services/icardfiles_service.h"

namespace oeav
{
	namespace service
	{
		class CardfilesService : public ICardfilesService
		{
		public:
			boost::shared_ptr<domain::AnalyticalAccountingCodeList> getAnalyticalAccountingCodes() const override;
		};
	}
}
