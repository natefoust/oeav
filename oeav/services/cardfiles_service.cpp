
// it's own header
#include "cardfiles_service.h"

#include "../repository/icardfiles_repository.h"
#include "../shared/instance_factory.h"


using namespace oeav::service;
using namespace oeav::domain;

boost::shared_ptr<AnalyticalAccountingCodeList> CardfilesService::getAnalyticalAccountingCodes() const
{
	InstanceFactory<domain::ICardfilesRepository>::getInstance()->getAnalyticalAccountingCodes();
	return boost::shared_ptr<AnalyticalAccountingCodeList>();
}