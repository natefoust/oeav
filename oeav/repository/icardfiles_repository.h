#pragma once

#include <boost/shared_ptr.hpp>

namespace oeav
{
	namespace domain
	{
		class AnalyticalAccountingCodeList;
		class AnalyticalTypeList;

		class ICardfilesRepository
		{
		public:
			// КАУ
			virtual boost::shared_ptr<AnalyticalAccountingCodeList> getAnalyticalAccountingCodes() const = 0;
			virtual void addAnalyticalAccountingCode(const std::string &analyticalCode, int typeId) const = 0;
			virtual void deleteAnalyticalAccountCode(int typeId) const = 0;
			virtual void updateAnalyticalAccountCode(int itemId, int typeId, const std::string &analyticalCode) const = 0;

			// Виды аналитики
			virtual boost::shared_ptr<AnalyticalTypeList> getAnalyticalTypes() const = 0;
			virtual void addAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const = 0;
			virtual void deleteAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const = 0;
			virtual void updateAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName,
				const std::string &analyticalCodeP, const std::string &analyticalNameP) const = 0;

		};
	}
}