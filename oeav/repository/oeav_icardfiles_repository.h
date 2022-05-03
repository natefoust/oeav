#pragma once

#include <boost/shared_ptr.hpp>
#include <vector>

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

		class ICardfilesRepository
		{
		public:
			//  ¿”
			virtual boost::shared_ptr<AnalyticalAccountingCodeList> getAnalyticalAccountingCodes() const = 0;
			virtual void addAnalyticalAccountingCode(const std::string &analyticalCode, int typeId) const = 0;
			virtual void deleteAnalyticalAccountCode(int typeId) const = 0;
			virtual void updateAnalyticalAccountCode(int itemId, int typeId, const std::string &analyticalCode) const = 0;
			virtual boost::shared_ptr<AnalyticalAccountingCode> getAnalyticalAccountingCode(int atId) const = 0;
			virtual boost::shared_ptr<AnalyticalAccountingCodeList> getAnalyticalAccountingCodes(int atId) const = 0;

			// ¬Ë‰˚ ‡Ì‡ÎËÚËÍË
			virtual boost::shared_ptr<AnalyticalTypeList> getAnalyticalTypes() const = 0;
			virtual void addAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const = 0;
			virtual void deleteAnalyticalType(int id) const = 0;
			virtual void updateAnalyticalType(int id, const std::string &analyticalCode, const std::string &analyticalName) const = 0;
			virtual int findIdByContent(const std::string &code, const std::string &name) const = 0;

			// œ—
			virtual boost::shared_ptr<AccountList> getAccounts() const = 0;
			virtual void updateAccount(int id, const std::string &code, const std::string &name,
				int typeId, int analyt1Id, int analyt2Id) const = 0;
			virtual void addAccount(const std::string &code, const std::string &name,
				int typeId, int analyt1Id, int analyt2Id) const = 0;
			virtual void deleteAccount(int id) const = 0;
			virtual int findAccIdByContent(const std::string &code, const std::string &name) const = 0;
			virtual std::vector<std::tuple<std::string, std::string>> getAccountsFromAccBook() const = 0;

			// Œœƒ
			virtual boost::shared_ptr<PrimaryDocumentList> getPrimaryDocuments() const = 0;
			virtual void updatePrimaryDocument(int id, const std::string &code, const std::string &name, int analyt1,
				int type1, int analyt2, int type2, int analyt3, int type3) const = 0;
			virtual void addPrimaryDocument(const std::string &code, const std::string &name, int analyt1,
				int type1, int analyt2, int type2, int analyt3, int type3) const = 0;
			virtual void deletePrimaryDocument(int id) const = 0;
			virtual int findOpdIdByContent(const std::string &code, const std::string &name) const = 0;
			virtual boost::shared_ptr<PrimaryDocument> getPrimaryDocument(int docId) const = 0;

			// “’Œ
			virtual boost::shared_ptr<TypicalOperationList> getTypicalOperations() const = 0;
			virtual void updateTypicalOperation(int id, int docId, const std::string &name, int debetIt, int creditId) const = 0;
			virtual void addTypicalOperation(int docId, const std::string &name, int debetIt, int creditId) const = 0;
			virtual void deleteTypicalOperation(int id) const = 0;
			virtual boost::shared_ptr<TypicalOperationList> getTypicalOperationsByDocId(int docId) const = 0;

		};
	}
}