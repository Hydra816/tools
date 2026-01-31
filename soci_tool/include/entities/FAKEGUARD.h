#ifndef FAKEGUARD_H
#define FAKEGUARD_H

#include "../oracle_db/IEntity.h"
#include <string>

// ================= FAKEGUARD实体定义 =================
struct FAKEGUARD: public IEntity {
    long long id;
    std::string gtprefix;
    std::string describe;
    std::string updatetime;
    std::string username;
    
    std::string name() const override { return "FAKEGUARD"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // FAKEGUARD_H