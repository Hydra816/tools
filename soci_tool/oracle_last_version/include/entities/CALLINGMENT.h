#ifndef CALLINGMENT_H
#define CALLINGMENT_H

#include "IEntity.h"
#include <string>

struct CALLINGMENT: public IEntity {
    long long id;
    std::string callingt;    // 注意：数据库中是CALLINGT不是CALLINGGT
    std::string action;
    std::string username;
    std::string group_name;  // 对应SQL中的"group"
    std::string updtime;
    std::string describe;
    long long groupid;
    
    std::string name() const override { return "CALLINGMENT"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // CALLINGMENT_H