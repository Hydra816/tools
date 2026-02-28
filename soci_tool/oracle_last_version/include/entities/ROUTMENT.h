#ifndef ROUTMENT_H
#define ROUTMENT_H

#include "IEntity.h"
#include <string>

struct ROUTMENT: public IEntity {
    long long id;
    std::string prefix;
    std::string username;
    std::string updtime;
    std::string describe;
    
    std::string name() const override { return "ROUTMENT"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // ROUTMENT_H