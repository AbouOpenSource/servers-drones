//
// Created by Maanrifa Bacar Ali on 20/01/2020.
//

#ifndef DRONEPROJECT_SERVICEPROVIDER_HPP
#define DRONEPROJECT_SERVICEPROVIDER_HPP


#include <string>

class ServiceProvider
{

protected:

    explicit ServiceProvider(std::string &name);

public:

    std::string get_name() const;

private:

    const std::string name_;

};


#endif //DRONEPROJECT_SERVICEPROVIDER_HPP
