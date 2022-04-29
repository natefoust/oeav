#include "../pch.h"
#include "instance_factory_impl.h"

#include "../services/cardfiles_service.h"
BIND_INSTANCE(oeav::service::ICardfilesService, oeav::service::CardfilesService)

#include "../repository/cardfiles_repository.h"
BIND_INSTANCE(oeav::domain::ICardfilesRepository, oeav::domain::CardfilesRepository)

#include "../services/documents_service.h"
BIND_INSTANCE(oeav::service::IDocumentsService, oeav::service::DocumentsService)

#include "../repository/documents_repository.h"
BIND_INSTANCE(oeav::domain::IDocumentsRepository, oeav::domain::DocumentsRepository)

#include "../shared/connection.h"
BIND_INSTANCE(oeav::domain::IConnection, oeav::domain::Connection)