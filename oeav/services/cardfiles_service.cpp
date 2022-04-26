
// it's own header
#include "cardfiles_service.h"

#include "../repository/icardfiles_repository.h"
#include "../shared/instance_factory.h"


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

	int pos = typeCode.find('-');
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
	return boost::shared_ptr<PrimaryDocumentList>();
}

void CardfilesService::updatePrimaryDocument(int id, const std::string &code, const std::string &name, int analyt1,
	int type1, int analyt2, int type2, int analyt3, int type3) const
{

}

void CardfilesService::addPrimaryDocument(const std::string &code, const std::string &name, int analyt1,
	int type1, int analyt2, int type2, int analyt3, int type3) const
{

}

void CardfilesService::deletePrimaryDocument(int id) const
{

}