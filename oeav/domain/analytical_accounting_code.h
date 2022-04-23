#pragma once

// std
#include <string>
#include <vector>

namespace oeav
{
	namespace domain
	{
		class AnalyticalAccountingCode
		{
		public:
			AnalyticalAccountingCode();
			AnalyticalAccountingCode(int id, int version, const std::string &analyticalType, const std::string &analyticalCode);

			void setAnalyticalType(std::string analyticalType);
			std::string getAnalyticalType();
			void setAnalyticalCode(std::string analyticalCode);
			std::string getAnalyticalCode();
			
			int getID();

		private:
			int _id;
			int _version;
			std::string _analyticalType;
			std::string _analyticalCode;
		};
		
		class AnalyticalAccountingCodeList : public std::vector<AnalyticalAccountingCode>
		{
		public:
			AnalyticalAccountingCodeList() {};
			AnalyticalAccountingCodeList(int size) 
				: std::vector<AnalyticalAccountingCode>(size) {};
		};
	}
}