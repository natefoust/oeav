#pragma once

#include "idocuments_repository.h"

namespace oeav
{
	namespace domain
	{
		class DocumentsRepository : public IDocumentsRepository
		{
		public:
			boost::shared_ptr<DocumentList> getDocuments() const override;
			void updateDocument(int id, int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const override;
			void deleteDocument(int id) const override;
			void addDocument(int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const override;
		};
	}
}