#include "SWITCHMENT.h"
#include <iostream>
#include <sstream>

void SWITCHMENT::print() const {
    // 由于字段太多，这里只打印部分关键字段，或者分行打印
    std::cout << "SWITCHMENT { id: " << id 
              << ", callinggtenb: \"" << callinggtenb
              << "\", spoofenb: \"" << spoofenb
              << "\", scanenb: \"" << scanenb
              << "\", floodenb: \"" << floodenb
              << "\" ... (更多字段)" << std::endl;
}

std::map<std::string, std::string> SWITCHMENT::to_map() const {
    std::map<std::string, std::string> result;
    result["ID"] = std::to_string(id);
    result["CALLINGGTENB"] = callinggtenb;
    result["SGTMISBLKENB"] = sgtmisblkenb;
    result["SGTBLKNUM"] = sgtblknum;
    result["SGTBLKTIME"] = sgtblktime;
    result["SGTBLKTTYPE"] = sgtblktype;
    result["SGTWHINUM"] = sgtwhinum;
    result["SGTWHITIME"] = sgtwhitime;
    result["SGTWHITTYPE"] = sgtwhitype;
    result["CALLEDGTENB"] = calledgtenb;
    result["DGTBLKNUM"] = dgtblknum;
    result["DGTBLKTIME"] = dgtblktime;
    result["DGTBLKTTYPE"] = dgtblktype;
    result["DGTWHINUM"] = dgtwhinum;
    result["DGTWHITIME"] = dgtwhitime;
    result["DGTWHITTYPE"] = dgtwhitype;
    result["SMSCGTENB"] = smscgtenb;
    result["SMGTBLKNUM"] = smgtblknum;
    result["SMGTBLKTIME"] = smgtblktime;
    result["SMGTBLKTTYPE"] = smgtblktype;
    result["SMGTWHINUM"] = smgtwhinum;
    result["SMGTWHITIME"] = smgtwhitime;
    result["SMGTWHITTYPE"] = smgtwhitype;
    result["IMSIENB"] = imsienb;
    result["IMSIBLKNUM"] = imsiblknum;
    result["IMSIBLKTIME"] = imsiblktime;
    result["IMSIBLKTTYPE"] = imsiblktype;
    result["IMSIWHINUM"] = imsiwhinum;
    result["IMSIWHITIME"] = imsiwhitime;
    result["IMSIWHITTYPE"] = imsiwhitype;
    result["MAPENB"] = mapenb;
    result["MAPBLKNUM"] = mapblknum;
    result["MAPBLKTIME"] = mapblktime;
    result["MAPBLKTTYPE"] = mapblktype;
    result["MAPWHINUM"] = mapwhinum;
    result["MAPWHITIME"] = mapwhitime;
    result["MAPWHITTYPE"] = mapwhitype;
    result["MATCHENB"] = matchenb;
    result["MATCHBLKNUM"] = matchblknum;
    result["MATCHBLKTIME"] = matchblktime;
    result["MATCHBLKTTYPE"] = matchblktype;
    result["MATCHWHINUM"] = matchwhinum;
    result["MATCHWHITIME"] = matchwhitime;
    result["MATCHWHITTYPE"] = matchwhitype;
    result["FAKEENB"] = fakeenb;
    result["FAKESRIVP"] = fakesrivp;
    result["FAKENUM"] = fakenum;
    result["FAKETIME"] = faketime;
    result["FAKETTYPE"] = faketype;
    result["SPOOFENB"] = spoofenb;
    result["SPOOFBLKNUM"] = spoofblknum;
    result["SPOOFBLKTIME"] = spoofblktime;
    result["SPOOFBLKTTYPE"] = spoofblktype;
    result["HOMEROUTENB"] = homerouteenb;
    result["HOMELOCGT"] = homelocgt;
    result["HOMECACHEVP"] = homecachevp;
    result["SCANENB"] = scanenb;
    result["SCANNUM"] = scannum;
    result["SCANTIME"] = scantime;
    result["SCANTTYPE"] = scanttype;
    result["FLOODENB"] = floodenb;
    result["MTSPOOFENB"] = mtspoofenb;
    result["MTSPOOFBLKNUM"] = mtspoofblknum;
    result["MTSPOOFBLKTIME"] = mtspoofblktime;
    result["MTSPOOFBLKTTYPE"] = mtspoofblktype;
    return result;
}

// 注册表到TableRegistry
static bool _reg_switchment = [](){
    TableRegistry::register_table<SWITCHMENT>();
    return true;
}();