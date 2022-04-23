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
			void addAnalyticalAccountingCode(const std::string &analyticalCode, int typeId) const override;
			void deleteAnalyticalAccountCode(int typeId) const override;
			void updateAnalyticalAccountCode(int itemId, int typeId, const std::string &analyticalCode) const override;

			void addAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const override;
			boost::shared_ptr<AnalyticalTypeList> getAnalyticalTypes() const override;
			void deleteAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const override;
			void updateAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName,
				const std::string &analyticalCodeP, const std::string &analyticalNameP) const override;
		};
	}
}