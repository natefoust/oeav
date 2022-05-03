#pragma once

// boost
#include <boost/shared_ptr.hpp>

#include "../domain/oeav_analytical_accounting_code.h"
#include "../domain/oeav_analytical_type.h"
#include "../domain/oeav_account.h"
#include "../domain/oeav_primary_document.h"
#include "../domain/oeav_typical_operation.h"
#include "../domain/oeav_document.h"
#include "../domain/oeav_acc_book_item.h"

namespace oeav
{
	namespace domain
	{
		class DocumentList;
		class RegBookItemList;
		class AccBookItemList;
	}

	namespace service
	{
		class IDocumentsService
		{
		public:
			virtual boost::shared_ptr<domain::DocumentList> getDocuments() const = 0;
			virtual void updateDocument(int id, int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const = 0;
			virtual void deleteDocument(int id) const = 0;
			virtual void addDocument(int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const = 0;

			virtual void registerDocument(const std::string & date, const std::string & docName, const std::string & docCode,
				const std::string & docDate, const std::string & operation, const std::string & debetCode, const std::string & debetName,
				const std::string & creditCode, const std::string & creditName, const std::string & sum, const std::string & debetT,
				const std::string & creditT) const = 0;
			virtual boost::shared_ptr<domain::RegBookItemList> getRegisteredDocuments() const = 0;

			virtual int generateAccountsBook() const = 0;
			virtual boost::shared_ptr<domain::AccBookItemList> getAccBookList() const = 0;

			virtual const std::string getBO() const = 0;
			virtual const std::string getJO() const = 0;

			virtual void updateDateFrom( std::string & date) const = 0;
			virtual void updateDateTo( std::string & date) const = 0;
			virtual void updateTargetAccount(const std::string &account) const = 0;
			virtual void updateCompanyName(const std::string &name) const = 0;
			virtual void updateCurrentDate( std::string & date) const = 0;

			virtual std::string getDateFrom() const = 0;
			virtual std::string getDateTo() const = 0;
			virtual std::string getTargetAccount() const = 0;
			virtual std::string getCompanyName() const = 0;
			virtual std::string getCurrentDate() const = 0;
		};
	}
}
