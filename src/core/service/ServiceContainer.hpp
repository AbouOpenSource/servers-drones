//
// Created by Maanrifa Bacar Ali on 02/01/2020.
//

#ifndef DRONEPROJECT_SERVICECONTAINER_HPP
#define DRONEPROJECT_SERVICECONTAINER_HPP


#include <map>
#include "../io/command/CommandContainer.hpp"
#include "ServiceProvider.hpp"

class ServiceContainer
{

public:

    static ServiceContainer* get_instance();

    void register_service(ServiceProvider* service);

    ServiceProvider* get_service(const std::string& service_id) const;

    bool has_service(const std::string& service_id) const;

private:

    static ServiceContainer* instance;

    ServiceContainer();

    std::map<std::string, ServiceProvider*> services_;

};

#endif //DRONEPROJECT_SERVICECONTAINER_HPP
