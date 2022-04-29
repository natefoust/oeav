#pragma once

#include "icardfiles_repository.h"

namespace oeav
{
	namespace domain
	{
		class CardfilesRepository : public ICardfilesRepository
		{
		public:
			boost::shared_ptr<AnalyticalAccountingCodeList> getAnalyticalAccountingCodes() const override;
			void addAnalyticalAccountingCode(const std::string &analyticalCode, int typeId) const override;
			void deleteAnalyticalAccountCode(int typeId) const override;
			void updateAnalyticalAccountCode(int itemId, int typeId, const std::string &analyticalCode) const override;
			boost::shared_ptr<AnalyticalAccountingCode> getAnalyticalAccountingCode(int atId) const override;
			boost::shared_ptr<AnalyticalAccountingCodeList> getAnalyticalAccountingCodes(int atId) const override;

			void addAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const override;
			boost::shared_ptr<AnalyticalTypeList> getAnalyticalTypes() const override;
			void deleteAnalyticalType(int id) const override;
			void updateAnalyticalType(int id, const std::string &analyticalCode, const std::string &analyticalName) const override;
			int findIdByContent(const std::string &code, const std::string &name) const override;

			boost::shared_ptr<AccountList> getAccounts() const override;
			void updateAccount(int id, const std::string &code, const std::string &name,
				int typeId, int analyt1Id, int analyt2Id) const override;
			void addAccount(const std::string &code, const std::string &name,
				int typeId, int analyt1Id, int analyt2Id) const override;
			void deleteAccount(int id) const override;
			int findAccIdByContent(const std::string &code, const std::string &name) const override;

			// нод
			boost::shared_ptr<domain::PrimaryDocumentList> getPrimaryDocuments() const override;
			void updatePrimaryDocument(int id, const std::string &code, const std::string &name, int analyt1,
				int type1, int analyt2, int type2, int analyt3, int type3) const override;
			void addPrimaryDocument(const std::string &code, const std::string &name, int analyt1,
				int type1, int analyt2, int type2, int analyt3, int type3) const override;
			void deletePrimaryDocument(int id) const override;
			int findOpdIdByContent(const std::string &code, const std::string &name) const override;
			boost::shared_ptr<PrimaryDocument> getPrimaryDocument(int docId) const override;

			// TXO
			boost::shared_ptr<TypicalOperationList> getTypicalOperations() const override;
			void updateTypicalOperation(int id, int docId, const std::string &name, int debetIt, int creditId) const override;
			void addTypicalOperation(int docId, const std::string &name, int debetIt, int creditId) const override;
			void deleteTypicalOperation(int id) const override;
			boost::shared_ptr<TypicalOperationList> getTypicalOperationsByDocId(int docId) const override;
		};
	}
}