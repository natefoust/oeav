#pragma once

#include <string>
#include <vector>

#include "account_types.h"
#include "analytical_type.h"

namespace oeav
{
	namespace domain
	{
		class PrimaryDocument
		{
		public:

			PrimaryDocument();
			PrimaryDocument(int id, const std::string &code, const std::string &name, AnalyticalType analyt1,
				AccountTypes type1, AnalyticalType analyt2, AccountTypes type2,
				AnalyticalType analyt3, AccountTypes type3);

			int getID();
			std::string getName();
			std::string getCode();
			AnalyticalType getAnalyt1();
			AccountTypes getType1();
			AnalyticalType getAnalyt2();
			AccountTypes getType2();
			AnalyticalType getAnalyt3();
			AccountTypes getType3();
			std::string getFullName();

			void setName(const std::string &name);
			void setCode(const std::string &code);
			void setAnalyt1(AnalyticalType type);
			void setType1(AccountTypes type);
			void setAnalyt2(AnalyticalType type);
			void setType2(AccountTypes type);
			void setAnalyt3(AnalyticalType type);
			void setType3(AccountTypes type);

		private:
			int _id;
			std::string _code;
			std::string _name;

			AnalyticalType _analyt1;
			AccountTypes _accountType1;

			AnalyticalType _analyt2;
			AccountTypes _accountType2;

			AnalyticalType _analyt3;
			AccountTypes _accountType3;
		};

		class PrimaryDocumentList : public std::vector<PrimaryDocument>
		{
		public:
			PrimaryDocumentList() {};
			PrimaryDocumentList(int size)
				: std::vector<PrimaryDocument>(size) {};
		};
	}
}
