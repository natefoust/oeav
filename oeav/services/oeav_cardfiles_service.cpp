
// it's own header
#include "oeav_cardfiles_service.h"

#include "../repository/oeav_icardfiles_repository.h"
#include "../shared/oeav_instance_factory.h"


using namespace oeav::service;
using namespace oeav::domain;

boost::shared_ptr<AnalyticalAccountingCodeList> CardfilesService::getAnalyticalAccountingCodes() const
{
	return InstanceFactory<domain::ICardfilesRepository>::getInstance()->
		getAnalyticalAccountingCodes();
}

void CardfilesService::addAnalyticalAccountingCode(const std::string &analyticalCode, int typeId) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->
		addAnalyticalAccountingCode(analyticalCode, typeId);
}

void CardfilesService::addAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->
		addAnalyticalType(analyticalCode, analyticalName);
}

boost::shared_ptr<AnalyticalTypeList> CardfilesService::getAnalyticalTypes() const
{
	return InstanceFactory<domain::ICardfilesRepository>::getInstance()->
		getAnalyticalTypes();
}

void CardfilesService::deleteAnalyticalType(int id) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->
		deleteAnalyticalType(id);
}

void CardfilesService::updateAnalyticalType(int id, const std::string &analyticalCode, const std::string &analyticalName) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->updateAnalyticalType(id, analyticalCode, analyticalName);
}

void CardfilesService::deleteAnalyticalAccountCode(int typeId) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->deleteAnalyticalAccountCode(typeId);
}

void CardfilesService::updateAnalyticalAccountCode(int itemId, int typeId, const std::string &analyticalCode) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->updateAnalyticalAccountCode(itemId, typeId, analyticalCode);
}

boost::shared_ptr<AccountList> CardfilesService::getAccounts() const
{
	return InstanceFactory<domain::ICardfilesRepository>::getInstance()->getAccounts();
}

int CardfilesService::findIdByContent(const std::string &type) const
{
	std::string typeCode{ type }, typeName{};

	size_t pos = typeCode.find('-');
	if (pos != std::string::npos)
	{
		typeName = typeCode.substr(pos + 2, typeCode.length() - pos);
		typeCode = typeCode.substr(0, pos - 1);

	}

	return InstanceFactory<domain::ICardfilesRepository>::getInstance()->findIdByContent(typeCode, typeName);
}

void CardfilesService::updateAccount(int id, const std::string &code, const std::string &name,
	int typeId, int analyt1Id, int analyt2Id) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->updateAccount(id, code, name, typeId, analyt1Id, analyt2Id);
}

void CardfilesService::addAccount(const std::string &code, const std::string &name,
	int typeId, int analyt1Id, int analyt2Id) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->addAccount(code, name, typeId, analyt1Id, analyt2Id);
}

void CardfilesService::deleteAccount(int id) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->deleteAccount(id);
}

boost::shared_ptr<PrimaryDocumentList> CardfilesService::getPrimaryDocuments() const
{
	return InstanceFactory<domain::ICardfilesRepository>::getInstance()->getPrimaryDocuments();
}

void CardfilesService::updatePrimaryDocument(int id, const std::string &code, const std::string &name, int analyt1,
	int type1, int analyt2, int type2, int analyt3, int type3) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->updatePrimaryDocument(id, code, name, analyt1,
		type1, analyt2, type2, analyt3, type3);
}

void CardfilesService::addPrimaryDocument(const std::string &code, const std::string &name, int analyt1,
	int type1, int analyt2, int type2, int analyt3, int type3) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->addPrimaryDocument(code, name, analyt1,
		type1, analyt2, type2, analyt3, type3);
}

void CardfilesService::deletePrimaryDocument(int id) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->deletePrimaryDocument(id);
}

boost::shared_ptr<TypicalOperationList> CardfilesService::getTypicalOperations() const
{
	return InstanceFactory<domain::ICardfilesRepository>::getInstance()->getTypicalOperations();
}

void CardfilesService::updateTypicalOperation(int id, int docId, const std::string &name, int debetIt, int creditId) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->updateTypicalOperation(id, docId, name, debetIt, creditId);
}

void CardfilesService::addTypicalOperation(int docId, const std::string &name, int debetIt, int creditId) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->addTypicalOperation(docId, name, debetIt, creditId);
}

void CardfilesService::deleteTypicalOperation(int id) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->deleteTypicalOperation(id);
}

int CardfilesService::findAccIdByContent(const std::string &content) const
{
	std::string typeCode{ content }, typeName{};

	size_t pos = typeCode.find('-');
	if (pos != std::string::npos)
	{
		typeName = typeCode.substr(pos + 2, typeCode.length() - pos);
		typeCode = typeCode.substr(0, pos - 1);

	}

	return InstanceFactory<domain::ICardfilesRepository>::getInstance()->findAccIdByContent(typeCode, typeName);
}

int CardfilesService::findOpdIdByContent(const std::string &content) const
{
	std::string typeCode{ content }, typeName{};

	size_t pos = typeCode.find('-');
	if (pos != std::string::npos)
	{
		typeName = typeCode.substr(pos + 2, typeCode.length() - pos);
		typeCode = typeCode.substr(0, pos - 1);

	}

	return InstanceFactory<domain::ICardfilesRepository>::getInstance()->findOpdIdByContent(typeCode, typeName);
}

boost::shared_ptr<PrimaryDocument> CardfilesService::getPrimaryDocument(int docId) const
{
	return InstanceFactory<domain::ICardfilesRepository>::getInstance()->getPrimaryDocument(docId);
}

boost::shared_ptr<TypicalOperationList> CardfilesService::getTypicalOperationsByDocId(int docId) const
{
	return InstanceFactory<ICardfilesRepository>::getInstance()->getTypicalOperationsByDocId(docId);
}

boost::shared_ptr<AnalyticalAccountingCode> CardfilesService::getAnalyticalAccountingCode(int atId) const
{
	return InstanceFactory<ICardfilesRepository>::getInstance()->getAnalyticalAccountingCode(atId);
}

boost::shared_ptr<AnalyticalAccountingCodeList> CardfilesService::getAnalyticalAccountingCodes(int atId) const
{
	return InstanceFactory<domain::ICardfilesRepository>::getInstance()->
		getAnalyticalAccountingCodes(atId);
}