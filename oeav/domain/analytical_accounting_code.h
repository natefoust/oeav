#pragma once

// std
#include <string>
#include <list>

namespace oeav
{
	namespace domain
	{
		class AnalyticalAccountingCode
		{
		public:
			AnalyticalAccountingCode();
			AnalyticalAccountingCode(int version, std::string analyticalType, std::string analyticalCode);

			void setAnalyticalType(std::string analyticalType);
			std::string getAnalyticalType();
			void setAnalyticalCode(std::string analyticalCode);
			std::string getAnalyticalCode();

		private:
			int _version;
			std::string _analyticalType;
			std::string _analyticalCode;
		};
		
		class AnalyticalAccountingCodeList : public std::list<AnalyticalAccountingCode>
		{
		public:
			AnalyticalAccountingCodeList() {};
			AnalyticalAccountingCodeList(int size) 
				: std::list<AnalyticalAccountingCode>(size) {};
		};
	}
}