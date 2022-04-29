#pragma once

#include <boost/shared_ptr.hpp>

namespace oeav
{
	namespace domain
	{
		class DocumentList;

		class IDocumentsRepository
		{
		public:
			virtual boost::shared_ptr<DocumentList> getDocuments() const = 0;
			virtual void updateDocument(int id, int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const = 0;
			virtual void deleteDocument(int id) const = 0;
			virtual void addDocument(int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const = 0;

		};
	}
}