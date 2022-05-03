#pragma once

#include <string>
#include <vector>

namespace oeav
{
	namespace domain
	{
		class AccBookItem
		{
		public:

			AccBookItem();
			AccBookItem(int id, const std::string &date, const std::string &docName, const std::string &docCode,
				const std::string &docDate, const std::string &operation, const std::string &accountCode, const std::string &accountName,
				const std::string &corCode, const std::string &corName, const std::string &sumDb,
				const std::string &sumKr);

			int getID();
			std::string getDate();
			std::string getDocName();
			std::string getDocCode();
			std::string getDocDate();
			std::string getOperation();
			std::string getAccountCode();
			std::string getAccountName();
			std::string getCorCode();
			std::string getCorName();
			std::string getSumDb();
			std::string getSumKr();

		private:
			int _id;
			std::string _date;
			std::string _docName;
			std::string _docCode;
			std::string _docDate;
			std::string _operation;
			std::string _accountCode;
			std::string _accountName;
			std::string _corCode;
			std::string _corName;
			std::string _sumDb;
			std::string _sumKr;
		};

		class AccBookItemList : public std::vector<AccBookItem>
		{
		public:
			AccBookItemList() {};
			AccBookItemList(int size)
				: std::vector<AccBookItem>(size) {};
		};
	}
}
