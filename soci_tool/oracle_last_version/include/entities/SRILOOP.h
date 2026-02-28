#ifndef SRILOOP_H
#define SRILOOP_H

#include "IEntity.h"
#include <string>

struct SRILOOP: public IEntity {
    long long id;
    long long detectedtime;
    long long detectednums;
    long long sriloopenb;
    
    std::string name() const override { return "SRILOOP"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // SRILOOP_H