//
// Created by Maanrifa Bacar Ali on 20/01/2020.
//

#include "ServiceProvider.hpp"

ServiceProvider::ServiceProvider(std::string &name): name_(name)
{}

std::string ServiceProvider::get_name() const
{
    return name_;
}
