#ifndef ROUTINGROUP_H
#define ROUTINGROUP_H

#include "IEntity.h"
#include <string>

struct ROUTINGROUP: public IEntity {
    long long id;
    std::string sccpgt;
    long long groupid;
    std::string updtime;
    std::string username;
    std::string group_name;  // 对应SQL中的"group"
    
    std::string name() const override { return "ROUTINGROUP"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // ROUTINGROUP_H