#ifndef FAKEMENT_H
#define FAKEMENT_H

#include "IEntity.h"
#include <string>

struct FAKEMENT: public IEntity {
    long long id;
    std::string smscgt;
    std::string maxnum;
    std::string username;
    std::string updtime;
    std::string describe;
    
    std::string name() const override { return "FAKEMENT"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // FAKEMENT_H