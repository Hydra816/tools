#ifndef IMSIMENT_H
#define IMSIMENT_H

#include "IEntity.h"
#include <string>

struct IMSIMENT: public IEntity {
    long long id;
    std::string imsi;
    std::string action;
    std::string username;
    std::string group_name;  // 对应SQL中的"group"
    std::string updtime;
    std::string describe;
    long long groupid;
    
    std::string name() const override { return "IMSIMENT"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // IMSIMENT_H