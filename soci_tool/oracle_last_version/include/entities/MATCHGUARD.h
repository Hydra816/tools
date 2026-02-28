#ifndef MATCHGUARD_H
#define MATCHGUARD_H

#include "IEntity.h"
#include <string>

struct MATCHGUARD: public IEntity {
    long long id;
    std::string name_;
    std::string describe;
    long long action;
    long long gtsmscmismatch;
    long long sidgtmismatch;
    long long sidsmscmismatch;
    long long senderidtype;
    long long phrasedataencoding;
    long long messagetype;
    long long sriloopdetected;
    std::string callinggt;
    std::string smscgt;
    std::string imsi;
    std::string phrase;
    std::string weightedkeywors;
    std::string sid;
    std::string rid;
    std::string updtime;
    std::string username;
    
    std::string name() const override { return "MATCHGUARD"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // MATCHGUARD_H