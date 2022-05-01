#pragma once

#include <string>
#include <vector>

#include "oeav_account.h"
#include "oeav_primary_document.h"

namespace oeav
{
	namespace domain
	{
		class TypicalOperation
		{
		public:

			TypicalOperation();
			TypicalOperation(int id, PrimaryDocument document, const std::string &name, Account debet, Account credit);

			int getID();
			std::string getName();
			PrimaryDocument getDocument();
			Account getDebet();
			Account getCredit();

			void setName(const std::string &name);
			void setDocument(PrimaryDocument document);
			void setDebet(Account debet);
			void setCredit(Account credit);

		private:
			int _id;
			PrimaryDocument _document;
			std::string _name;
			Account _debet;
			Account _credit;
		};

		class TypicalOperationList : public std::vector<TypicalOperation>
		{
		public:
			TypicalOperationList() {};
			TypicalOperationList(int size)
				: std::vector<TypicalOperation>(size) {};
		};
	}
}
