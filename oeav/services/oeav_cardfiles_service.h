#pragma once

// it's own interface
#include "../services/oeav_icardfiles_service.h"

namespace oeav
{
	namespace service
	{
		class CardfilesService : public ICardfilesService
		{
		public:
			boost::shared_ptr<domain::AnalyticalAccountingCodeList> getAnalyticalAccountingCodes() const override;
			void addAnalyticalAccountingCode(const std::string &analyticalCode, int typeId) const override;
			void deleteAnalyticalAccountCode(int typeId) const override;
			void updateAnalyticalAccountCode(int itemId, int typeId, const std::string &analyticalCode) const override;
			boost::shared_ptr<domain::AnalyticalAccountingCode> getAnalyticalAccountingCode(int atId) const override;
			boost::shared_ptr<domain::AnalyticalAccountingCodeList> getAnalyticalAccountingCodes(int atId) const override;

			void addAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const override;
			boost::shared_ptr<domain::AnalyticalTypeList> getAnalyticalTypes() const override;
			void deleteAnalyticalType(int id) const override;
		    void updateAnalyticalType(int id, const std::string &analyticalCode, const std::string &analyticalName) const override;
			int findIdByContent(const std::string &type) const override;

			boost::shared_ptr<domain::AccountList> getAccounts() const override;
			void updateAccount(int id, const std::string &code, const std::string &name,
				int typeId, int analyt1Id, int analyt2Id) const override;
			void addAccount(const std::string &code, const std::string &name,
				int typeId, int analyt1Id, int analyt2Id) const override;
			void deleteAccount(int id) const override;
			int findAccIdByContent(const std::string &content) const override;
			std::vector<std::tuple<std::string, std::string>> getAccountsFromAccBook() const override;

			// ???
			boost::shared_ptr<domain::PrimaryDocumentList> getPrimaryDocuments() const override;
			void updatePrimaryDocument(int id, const std::string &code, const std::string &name, int analyt1,
				int type1, int analyt2, int type2, int analyt3, int type3) const override;
			void addPrimaryDocument(const std::string &code, const std::string &name, int analyt1,
				int type1, int analyt2, int type2, int analyt3, int type3) const override;
			void deletePrimaryDocument(int id) const override;
			int findOpdIdByContent(const std::string &content) const override;
			boost::shared_ptr<domain::PrimaryDocument> getPrimaryDocument(int docId) const override;

			boost::shared_ptr<domain::TypicalOperationList> getTypicalOperations() const override;
			void updateTypicalOperation(int id, int docId, const std::string &name, int debetIt, int creditId) const override;
			void addTypicalOperation(int docId, const std::string &name, int debetIt, int creditId) const override;
			void deleteTypicalOperation(int id) const override;
			boost::shared_ptr<domain::TypicalOperationList> getTypicalOperationsByDocId(int docId) const override;
		};
	}
}
