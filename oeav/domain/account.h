#pragma once

#include <string>
#include <vector>

#include "account_types.h"
#include "analytical_type.h"

namespace oeav
{
	namespace domain
	{
		class Account
		{
		public:

			Account();
			Account(int id, const std::string &name, const std::string &code, AccountTypes type,
				AnalyticalType analyt1, AnalyticalType analyt2);

			int getID();
			std::string getName();
			std::string getCode();
			AccountTypes getType();
			AnalyticalType getAnalyt1();
			AnalyticalType getAnalyt2();
			std::string getFullName();

			void setName(const std::string &name);
			void setCode(const std::string &code);
			void setType(AccountTypes type);
			void setAnalyt1(AnalyticalType type);
			void setAnalyt2(AnalyticalType type);

		private:
			int _id;
			std::string _code;
			std::string _name;
			AccountTypes _accountType;
			AnalyticalType _analyt1;
			AnalyticalType _analyt2;
		};

		class AccountList : public std::vector<Account>
		{
		public:
			AccountList() {};
			AccountList(int size)
				: std::vector<Account>(size) {};
		};
	}
}
