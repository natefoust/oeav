#pragma once

// boost
#include <boost/shared_ptr.hpp>

#include "../domain/oeav_analytical_accounting_code.h"
#include "../domain/oeav_analytical_type.h"
#include "../domain/oeav_account.h"
#include "../domain/oeav_primary_document.h"
#include "../domain/oeav_typical_operation.h"

namespace oeav
{
	namespace domain
	{
		class AnalyticalAccountingCodeList;
		class AnalyticalTypeList;
		class AccountList;
		class PrimaryDocumentList;
		class TypicalOperationList;
		class PrimaryDocument;
		class AnalyticalAccountingCode;
	}

	namespace service
	{
		class ICardfilesService
		{
		public:
			virtual boost::shared_ptr<domain::AnalyticalAccountingCodeList> getAnalyticalAccountingCodes() const = 0;
			virtual void addAnalyticalAccountingCode(const std::string &analyticalCode, int typeId) const = 0;
			virtual void deleteAnalyticalAccountCode(int typeId) const = 0;
			virtual void updateAnalyticalAccountCode(int itemId, int typeId, const std::string &analyticalCode) const = 0;
			virtual boost::shared_ptr<domain::AnalyticalAccountingCode> getAnalyticalAccountingCode(int atId) const = 0;
			virtual boost::shared_ptr<domain::AnalyticalAccountingCodeList> getAnalyticalAccountingCodes(int atId) const = 0;

			// Виды аналитики
			virtual boost::shared_ptr<domain::AnalyticalTypeList> getAnalyticalTypes() const = 0;
			virtual void addAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const = 0;
			virtual void deleteAnalyticalType(int id) const = 0;
			virtual void updateAnalyticalType(int id, const std::string &analyticalCode, const std::string &analyticalName) const = 0;
			virtual int findIdByContent(const std::string &type) const = 0;

			// ПС
			virtual boost::shared_ptr<domain::AccountList> getAccounts() const = 0;
			virtual void updateAccount(int id, const std::string &code, const std::string &name,
				int typeId, int analyt1Id, int analyt2Id) const = 0;
			virtual void addAccount(const std::string &code, const std::string &name,
				int typeId, int analyt1Id, int analyt2Id) const = 0;
			virtual void deleteAccount(int id) const = 0;
			virtual int findAccIdByContent(const std::string &content) const = 0;

			// ОПД
			virtual boost::shared_ptr<domain::PrimaryDocumentList> getPrimaryDocuments() const = 0;
			virtual void updatePrimaryDocument(int id, const std::string &code, const std::string &name, int analyt1,
				int type1, int analyt2, int type2, int analyt3, int type3) const = 0;
			virtual void addPrimaryDocument(const std::string &code, const std::string &name, int analyt1,
				int type1, int analyt2, int type2, int analyt3, int type3) const = 0;
			virtual void deletePrimaryDocument(int id) const = 0;
			virtual int findOpdIdByContent(const std::string &content) const = 0;
			virtual boost::shared_ptr<domain::PrimaryDocument> getPrimaryDocument(int docId) const = 0;

			// ТХО
			virtual boost::shared_ptr<domain::TypicalOperationList> getTypicalOperations() const = 0;
			virtual void updateTypicalOperation(int id, int docId, const std::string &name, int debetIt, int creditId) const = 0;
			virtual void addTypicalOperation(int docId, const std::string &name, int debetIt, int creditId) const = 0;
			virtual void deleteTypicalOperation(int id) const = 0;
			virtual boost::shared_ptr<domain::TypicalOperationList> getTypicalOperationsByDocId(int docId) const = 0;
		};
	}
}
