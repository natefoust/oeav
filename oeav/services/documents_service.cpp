
// it's own header
#include "documents_service.h"

#include <boost/algorithm/string/replace.hpp>

#include "../repository/idocuments_repository.h"
#include "../shared/instance_factory.h"


using namespace oeav::service;
using namespace oeav::domain;

boost::shared_ptr<DocumentList> DocumentsService::getDocuments() const
{
	return InstanceFactory<IDocumentsRepository>::getInstance()->getDocuments();
}

void DocumentsService::updateDocument(int id, int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const
{
	boost::algorithm::replace_all(date, ".", "-");

	InstanceFactory<domain::IDocumentsRepository>::getInstance()->updateDocument(id, doc, oper, sum, date, kau1, kau2, kau3);
}

void DocumentsService::deleteDocument(int id) const
{
	InstanceFactory<domain::IDocumentsRepository>::getInstance()->deleteDocument(id);
}

void DocumentsService::addDocument(int doc, int oper, const std::string &sum, std::string date, int kau1, int kau2, int kau3) const
{
	boost::algorithm::replace_all(date, ".", "-");

	InstanceFactory<domain::IDocumentsRepository>::getInstance()->addDocument(doc, oper, sum, date, kau1, kau2, kau3);
}