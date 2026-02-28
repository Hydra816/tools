#ifndef SWITCHMENT_H
#define SWITCHMENT_H

#include "IEntity.h"
#include <string>

struct SWITCHMENT: public IEntity {
    long long id;
    std::string callinggtenb;
    std::string sgtmisblkenb;
    std::string sgtblknum;
    std::string sgtblktime;
    std::string sgtblktype;
    std::string sgtwhinum;
    std::string sgtwhitime;
    std::string sgtwhitype;
    std::string calledgtenb;
    std::string dgtblknum;
    std::string dgtblktime;
    std::string dgtblktype;
    std::string dgtwhinum;
    std::string dgtwhitime;
    std::string dgtwhitype;
    std::string smscgtenb;
    std::string smgtblknum;
    std::string smgtblktime;
    std::string smgtblktype;
    std::string smgtwhinum;
    std::string smgtwhitime;
    std::string smgtwhitype;
    std::string imsienb;
    std::string imsiblknum;
    std::string imsiblktime;
    std::string imsiblktype;
    std::string imsiwhinum;
    std::string imsiwhitime;
    std::string imsiwhitype;
    std::string mapenb;
    std::string mapblknum;
    std::string mapblktime;
    std::string mapblktype;
    std::string mapwhinum;
    std::string mapwhitime;
    std::string mapwhitype;
    std::string matchenb;
    std::string matchblknum;
    std::string matchblktime;
    std::string matchblktype;
    std::string matchwhinum;
    std::string matchwhitime;
    std::string matchwhitype;
    std::string fakeenb;
    std::string fakesrivp;
    std::string fakenum;
    std::string faketime;
    std::string faketype;
    std::string spoofenb;
    std::string spoofblknum;
    std::string spoofblktime;
    std::string spoofblktype;
    std::string homerouteenb;
    std::string homelocgt;
    std::string homecachevp;
    std::string scanenb;
    std::string scannum;
    std::string scantime;
    std::string scanttype;
    std::string floodenb;
    std::string mtspoofenb;
    std::string mtspoofblknum;
    std::string mtspoofblktime;
    std::string mtspoofblktype;
    
    std::string name() const override { return "SWITCHMENT"; }
    void print() const override;
    std::map<std::string, std::string> to_map() const override;
};

#endif // SWITCHMENT_H