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
			void addAnalyticalAccountingCode(const std::string &analyticalCode, int typeId) const override;
			void deleteAnalyticalAccountCode(int typeId) const override;
			void updateAnalyticalAccountCode(int itemId, int typeId, const std::string &analyticalCode) const override;

			void addAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const override;
			boost::shared_ptr<domain::AnalyticalTypeList> getAnalyticalTypes() const override;
			void deleteAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const override;
		    void updateAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName,
				const std::string &analyticalCodeP, const std::string &analyticalNameP) const override;
		};
	}
}
