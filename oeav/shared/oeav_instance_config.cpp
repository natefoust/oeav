#include "../pch.h"
#include "instance_factory_impl.h"

#include "../services/cardfiles_service.h"
BIND_INSTANCE(oeav::service::ICardfilesService, oeav::service::CardfilesService)

#include "../repository/cardfiles_repository.h"
BIND_INSTANCE(oeav::domain::ICardfilesRepository, oeav::domain::CardfilesRepository)

#include "../shared/connection.h"
BIND_INSTANCE(oeav::domain::IConnection, oeav::domain::Connection)