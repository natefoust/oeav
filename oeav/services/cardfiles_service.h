#pragma once

// it's own interface
#include "../services/icardfiles_service.h"

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

			// нод
			boost::shared_ptr<domain::PrimaryDocumentList> getPrimaryDocuments() const override;
			void updatePrimaryDocument(int id, const std::string &code, const std::string &name, int analyt1,
				int type1, int analyt2, int type2, int analyt3, int type3) const override;
			void addPrimaryDocument(const std::string &code, const std::string &name, int analyt1,
				int type1, int analyt2, int type2, int analyt3, int type3) const override;
			void deletePrimaryDocument(int id) const override;
		};
	}
}
