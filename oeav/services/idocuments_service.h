#pragma once

// boost
#include <boost/shared_ptr.hpp>

#include "../domain/analytical_accounting_code.h"
#include "../domain/analytical_type.h"
#include "../domain/account.h"
#include "../domain/oeav_primary_document.h"
#include "../domain/typical_operation.h"
#include "../domain/document.h"

namespace oeav
{
	namespace domain
	{
		class DocumentList;
	}

	namespace service
	{
		class IDocumentsService
		{
		public:
			virtual boost::shared_ptr<domain::DocumentList> getDocuments() const = 0;
			virtual void updateDocument(int id, int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const = 0;
			virtual void deleteDocument(int id) const = 0;
			virtual void addDocument(int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const = 0;
		};
	}
}
