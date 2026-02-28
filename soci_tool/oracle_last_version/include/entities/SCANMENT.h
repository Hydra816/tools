#ifndef SCANMENT_H
#define SCANMENT_H

#include "IEntity.h"
#include <string>

struct SCANMENT: public IEntity {
    long long id;
    std::string monum;
    std::string reset;
    std::string blkdur;
    std::string username;
    std::string updtime;
    std::string describe;
    
    std::string name() const override { return "SCANMENT"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // SCANMENT_H