#pragma once

// std
#include <string>
#include <vector>

#include "oeav_analytical_type.h"

namespace oeav
{
	namespace domain
	{
		class AnalyticalAccountingCode
		{
		public:
			AnalyticalAccountingCode();
			AnalyticalAccountingCode(int id, int version, AnalyticalType analyticalType, const std::string &analyticalCode);

			void setAnalyticalType(AnalyticalType analyticalType);
			AnalyticalType getAnalyticalType();

			void setAnalyticalCode(std::string analyticalCode);
			std::string getAnalyticalCode();
			
			int getID();

		private:
			int _id;
			int _version;
			AnalyticalType _analyticalType;
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