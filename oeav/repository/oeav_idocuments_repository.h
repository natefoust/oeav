#pragma once

#include <boost/shared_ptr.hpp>

namespace oeav
{
	namespace domain
	{
		class DocumentList;
		class RegBookItemList;

		class IDocumentsRepository
		{
		public:
			virtual boost::shared_ptr<DocumentList> getDocuments() const = 0;
			virtual void updateDocument(int id, int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const = 0;
			virtual void deleteDocument(int id) const = 0;
			virtual void addDocument(int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const = 0;

			virtual void registerDocument(const std::string & date, const std::string & docName, const std::string & docCode,
				const std::string & docDate, const std::string & operation, const std::string & debetCode, const std::string & debetName,
				const std::string & creditCode, const std::string & creditName, const std::string & sum, const std::string & debetT,
				const std::string & creditT) const = 0;
			virtual boost::shared_ptr<RegBookItemList> getRegisteredDocuments() const = 0;

		};
	}
}