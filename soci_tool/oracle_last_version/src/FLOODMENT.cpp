#include "FLOODMENT.h"
#include <iostream>
#include <sstream>

void FLOODMENT::print() const {
    std::cout << "FLOODMENT { id: " << id 
              << ", category: \"" << category
              << "\", paramter: \"" << paramter
              << "\", maplimit: \"" << maplimit
              << "\", obeyglobal: \"" << obeyglobal
              << "\", username: \"" << username
              << "\", updtime: \"" << updtime
              << "\", describe: \"" << describe
              << "\" }" << std::endl;
}

std::map<std::string, std::string> FLOODMENT::to_map() const {
    std::map<std::string, std::string> result;
    result["ID"] = std::to_string(id);
    result["CATEGORY"] = category;
    result["PARAMTER"] = paramter;
    result["MAPLIMIT"] = maplimit;
    result["OBEYGLOBAL"] = obeyglobal;
    result["USERNAME"] = username;
    result["UPDTIME"] = updtime;
    result["DESCRIBE"] = describe;
    return result;
}

// 注册表到TableRegistry
static bool _reg_floodment = [](){
    TableRegistry::register_table<FLOODMENT>();
    return true;
}();