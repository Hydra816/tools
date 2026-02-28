#ifndef SPOOFMENT_H
#define SPOOFMENT_H

#include "IEntity.h"
#include <string>

struct SPOOFMENT: public IEntity {
    long long id;
    std::string prefix;
    std::string username;
    std::string updtime;
    std::string describe;
    
    std::string name() const override { return "SPOOFMENT"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // SPOOFMENT_H