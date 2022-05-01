#include "../pch.h"
#include "oeav_instance_factory_impl.h"

#include "../services/oeav_cardfiles_service.h"
BIND_INSTANCE(oeav::service::ICardfilesService, oeav::service::CardfilesService)

#include "../repository/oeav_cardfiles_repository.h"
BIND_INSTANCE(oeav::domain::ICardfilesRepository, oeav::domain::CardfilesRepository)

#include "../services/oeav_documents_service.h"
BIND_INSTANCE(oeav::service::IDocumentsService, oeav::service::DocumentsService)

#include "../repository/oeav_documents_repository.h"
BIND_INSTANCE(oeav::domain::IDocumentsRepository, oeav::domain::DocumentsRepository)

#include "../shared/oeav_connection.h"
BIND_INSTANCE(oeav::domain::IConnection, oeav::domain::Connection)