//
// Created by Maanrifa Bacar Ali on 02/01/2020.
//

#include "ServiceContainer.hpp"

ServiceContainer* ServiceContainer::instance = nullptr;

ServiceContainer::ServiceContainer() : services_({})
{}

ServiceContainer* ServiceContainer::get_instance()
{
    if (instance == nullptr)
    {
        instance = new ServiceContainer();
    }

    return instance;
}

void ServiceContainer::register_service(ServiceProvider* service)
{
    services_.insert({service->get_name(), service});
}

ServiceProvider *ServiceContainer::get_service(const std::string& service_id) const
{
    return has_service(service_id) ? services_.at(service_id) : nullptr;
}

bool ServiceContainer::has_service(const std::string& service_id) const
{
    return services_.find(service_id) != services_.end();
}

