#ifndef CALLEDMENT_H
#define CALLEDMENT_H

#include "IEntity.h"
#include <string>

struct CALLEDMENT: public IEntity {
    long long id;
    std::string calledgt;
    std::string action;
    std::string username;
    std::string group_name;  // 对应SQL中的"group"
    std::string updtime;
    std::string describe;
    long long groupid;
    
    std::string name() const override { return "CALLEDMENT"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // CALLEDMENT_H