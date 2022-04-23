
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

void CardfilesService::deleteAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->
		deleteAnalyticalType(analyticalCode, analyticalName);
}

void CardfilesService::updateAnalyticalType(const std::string &analyticalCode, const std::string &analyticalName,
	const std::string &analyticalCodeP, const std::string &analyticalNameP) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->updateAnalyticalType(analyticalCode, analyticalName, analyticalCodeP, analyticalNameP);
}

void CardfilesService::deleteAnalyticalAccountCode(int typeId) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->deleteAnalyticalAccountCode(typeId);
}

void CardfilesService::updateAnalyticalAccountCode(int itemId, int typeId, const std::string &analyticalCode) const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->updateAnalyticalAccountCode(itemId, typeId, analyticalCode);
}