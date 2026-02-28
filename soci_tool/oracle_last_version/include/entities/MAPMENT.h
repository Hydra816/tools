#ifndef MAPMENT_H
#define MAPMENT_H

#include "IEntity.h"
#include <string>

struct MAPMENT: public IEntity {
    long long id;
    std::string gt;
    std::string country;
    std::string openum;
    std::string action;
    std::string username;
    std::string updtime;
    std::string describe;
    
    std::string name() const override { return "MAPMENT"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // MAPMENT_H