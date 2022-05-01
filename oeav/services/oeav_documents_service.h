#pragma once

// it's own interface
#include "../services/oeav_idocuments_service.h"

namespace oeav
{
	namespace service
	{
		class DocumentsService : public IDocumentsService
		{
		public:
			boost::shared_ptr<domain::DocumentList> getDocuments() const override;
			void updateDocument(int id, int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const override;
			void deleteDocument(int id) const override;
			void addDocument(int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const override;
			
			void registerDocument(const std::string & date, const std::string & docName, const std::string & docCode,
				const std::string & docDate, const std::string & operation, const std::string & debetCode, const std::string & debetName,
				const std::string & creditCode, const std::string & creditName, const std::string & sum, const std::string & debetT,
				const std::string & creditT) const override;
			boost::shared_ptr<domain::RegBookItemList> getRegisteredDocuments() const override;
		};
	}
}
