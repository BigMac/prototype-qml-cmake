#include "ResourceRepositoryService.h"

ResourceRepositoryService::ResourceRepositoryService(std::shared_ptr<Dispatcher> dispatcher) :
     boost::msm::back::state_machine<ResourceRepositoryFsm>(dispatcher)
{
}
