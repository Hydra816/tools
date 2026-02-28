#include "MAPMENT.h"
#include <iostream>
#include <sstream>

void MAPMENT::print() const {
    std::cout << "MAPMENT { id: " << id 
              << ", gt: \"" << gt
              << "\", country: \"" << country
              << "\", openum: \"" << openum
              << "\", action: \"" << action
              << "\", username: \"" << username
              << "\", updtime: \"" << updtime
              << "\", describe: \"" << describe
              << "\" }" << std::endl;
}

std::map<std::string, std::string> MAPMENT::to_map() const {
    std::map<std::string, std::string> result;
    result["ID"] = std::to_string(id);
    result["GT"] = gt;
    result["COUNTRY"] = country;
    result["OPENUM"] = openum;
    result["ACTION"] = action;
    result["USERNAME"] = username;
    result["UPDTIME"] = updtime;
    result["DESCRIBE"] = describe;
    return result;
}

// 注册表到TableRegistry
static bool _reg_mapment = [](){
    TableRegistry::register_table<MAPMENT>();
    return true;
}();