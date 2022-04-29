#pragma once

// it's own interface
#include "../services/idocuments_service.h"

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
		};
	}
}
