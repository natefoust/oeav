
// it's own header
#include "oeav_documents_service.h"

#include <boost/algorithm/string/replace.hpp>

#include "../repository/oeav_idocuments_repository.h"
#include "../shared/oeav_instance_factory.h"


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

void DocumentsService::registerDocument(const std::string & date, const std::string & docName, const std::string & docCode,
	const std::string & docDate, const std::string & operation, const std::string & debetCode, const std::string & debetName,
	const std::string & creditCode, const std::string & creditName, const std::string & sum, const std::string & debetT,
	const std::string & creditT) const
{
	InstanceFactory<domain::IDocumentsRepository>::getInstance()->registerDocument(date, docName, docCode, docDate, operation,
		debetCode, debetName, creditCode, creditName, sum, debetT, creditT);
}

boost::shared_ptr<RegBookItemList> DocumentsService::getRegisteredDocuments() const
{
	return InstanceFactory<domain::IDocumentsRepository>::getInstance()->getRegisteredDocuments();
}

int DocumentsService::generateAccountsBook() const
{
	return InstanceFactory<domain::IDocumentsRepository>::getInstance()->generateAccountsBook();
}

boost::shared_ptr<AccBookItemList> DocumentsService::getAccBookList() const
{
	return InstanceFactory<domain::IDocumentsRepository>::getInstance()->getAccBookList();
}

const std::string DocumentsService::getBO() const
{
	return InstanceFactory<domain::IDocumentsRepository>::getInstance()->getBO();
}

const std::string DocumentsService::getJO() const
{
	return InstanceFactory<domain::IDocumentsRepository>::getInstance()->getJO();
}

void DocumentsService::updateDateFrom(std::string & date) const
{
	boost::algorithm::replace_all(date, ".", "-");

	InstanceFactory<domain::IDocumentsRepository>::getInstance()->updateDateFrom(date);
}

void DocumentsService::updateDateTo(std::string & date) const
{
	boost::algorithm::replace_all(date, ".", "-");

	InstanceFactory<domain::IDocumentsRepository>::getInstance()->updateDateTo(date);
}

void DocumentsService::updateTargetAccount(const std::string &account) const
{
	std::string typeCode{ account }, typeName{};

	size_t pos = typeCode.find('-');
	if (pos != std::string::npos)
	{
		typeName = typeCode.substr(pos + 2, typeCode.length() - pos);
		typeCode = typeCode.substr(0, pos - 1);

	}
	
	InstanceFactory<domain::IDocumentsRepository>::getInstance()->updateTargetAccount(typeCode, typeName);
}

void DocumentsService::updateCompanyName(const std::string &name) const
{
	InstanceFactory<domain::IDocumentsRepository>::getInstance()->updateCompanyName(name);
}

void DocumentsService::updateCurrentDate(std::string & date) const
{
	boost::algorithm::replace_all(date, ".", "-");

	InstanceFactory<domain::IDocumentsRepository>::getInstance()->updateCurrentDate(date);
}

std::string DocumentsService::getDateFrom() const
{
	return InstanceFactory<domain::IDocumentsRepository>::getInstance()->getDateFrom();
}

std::string DocumentsService::getDateTo() const
{
	return InstanceFactory<domain::IDocumentsRepository>::getInstance()->getDateTo();
}

std::string DocumentsService::getTargetAccount() const
{
	return InstanceFactory<domain::IDocumentsRepository>::getInstance()->getTargetAccount();
}

std::string DocumentsService::getCompanyName() const
{
	return InstanceFactory<domain::IDocumentsRepository>::getInstance()->getCompanyName();
}

std::string DocumentsService::getCurrentDate() const
{
	return InstanceFactory<domain::IDocumentsRepository>::getInstance()->getCurrentDate();
}

const std::string DocumentsService::getKS() const
{
	return InstanceFactory<domain::IDocumentsRepository>::getInstance()->getKS();
}

const std::string DocumentsService::getOSV() const
{
	return InstanceFactory<domain::IDocumentsRepository>::getInstance()->getOSV();
}