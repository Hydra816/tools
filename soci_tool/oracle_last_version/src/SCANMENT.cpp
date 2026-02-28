#include "SCANMENT.h"
#include <iostream>
#include <sstream>

void SCANMENT::print() const {
    std::cout << "SCANMENT { id: " << id 
              << ", monum: \"" << monum
              << "\", reset: \"" << reset
              << "\", blkdur: \"" << blkdur
              << "\", username: \"" << username
              << "\", updtime: \"" << updtime
              << "\", describe: \"" << describe
              << "\" }" << std::endl;
}

std::map<std::string, std::string> SCANMENT::to_map() const {
    std::map<std::string, std::string> result;
    result["ID"] = std::to_string(id);
    result["MONUM"] = monum;
    result["RESET"] = reset;
    result["BLKDUR"] = blkdur;
    result["USERNAME"] = username;
    result["UPDTIME"] = updtime;
    result["DESCRIBE"] = describe;
    return result;
}

// 注册表到TableRegistry
static bool _reg_scanment = [](){
    TableRegistry::register_table<SCANMENT>();
    return true;
}();