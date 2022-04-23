#pragma once

// std
#include <string>
#include <vector>

namespace oeav
{
	namespace domain
	{
		class AnalyticalType
		{
		public:
			AnalyticalType();
			AnalyticalType(int id, const std::string &analyticalCode, const std::string &analyticalName);

			void setAnalyticalName(const std::string &analyticalType);
			std::string getAnalyticalName();
			void setAnalyticalCode(const std::string &analyticalCode);
			std::string getAnalyticalCode();
			int getID();

		private:
			int _id;
			std::string _analyticalCode;
			std::string _analyticalName;
		};
		
		class AnalyticalTypeList : public std::vector<AnalyticalType>
		{
		public:
			AnalyticalTypeList() {};
			AnalyticalTypeList(int size)
				: std::vector<AnalyticalType>(size) {};
		};
	}
}