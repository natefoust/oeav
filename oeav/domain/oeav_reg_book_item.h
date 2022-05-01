#pragma once

#include <string>
#include <vector>

#include "oeav_account_types.h"
#include "oeav_analytical_type.h"

namespace oeav
{
	namespace domain
	{
		class RegBookItem
		{
		public:

			RegBookItem();
			RegBookItem(int id, const std::string &date, const std::string &docName, const std::string &docCode,
				const std::string &docDate, const std::string &operation, const std::string &debetCode, const std::string &debetName,
				const std::string &creditCode, const std::string &creditName, const std::string &sum,
				const std::string &debetT, const std::string &creditT);

			int getID();
			std::string getDate();
			std::string getDocName();
			std::string getDocCode();
			std::string getDocDate();
			std::string getOperation();
			std::string getDebetCode();
			std::string getDebetName();
			std::string getCreditCode();
			std::string getCreditName();
			std::string getSum();
			std::string getDebetT();
			std::string getCreditT();

		private:
			int _id;
			std::string _date;
			std::string _docName;
			std::string _docCode;
			std::string _docDate;
			std::string _operation;
			std::string _debetCode;
			std::string _debetName;
			std::string _creditCode;
			std::string _creditName;
			std::string _sum;
			std::string _debetT;
			std::string _creditT;
		};

		class RegBookItemList : public std::vector<RegBookItem>
		{
		public:
			RegBookItemList() {};
			RegBookItemList(int size)
				: std::vector<RegBookItem>(size) {};
		};
	}
}
