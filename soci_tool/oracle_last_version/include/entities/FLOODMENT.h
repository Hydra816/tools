#ifndef FLOODMENT_H
#define FLOODMENT_H

#include "IEntity.h"
#include <string>

struct FLOODMENT: public IEntity {
    long long id;
    std::string category;
    std::string paramter;
    std::string maplimit;
    std::string obeyglobal;
    std::string username;
    std::string updtime;
    std::string describe;
    
    std::string name() const override { return "FLOODMENT"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // FLOODMENT_H