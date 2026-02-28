#ifndef SMSCMENT_H
#define SMSCMENT_H

#include "IEntity.h"
#include <string>

struct SMSCMENT: public IEntity {
    long long id;
    std::string smscgt;
    std::string msgty;
    std::string action;      // 对应SQL中的"action"
    std::string username;
    std::string group_name;  // 对应SQL中的"group"
    std::string updtime;
    std::string describe;    // 对应SQL中的"describe"
    long long groupid;
    
    std::string name() const override { return "SMSCMENT"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // SMSCMENT_H