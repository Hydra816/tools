#include "CALLEDMENT.h"
#include <iostream>
#include <sstream>

void CALLEDMENT::print() const {
    std::cout << "CALLEDMENT { id: " << id 
              << ", calledgt: \"" << calledgt
              << "\", action: \"" << action
              << "\", username: \"" << username
              << "\", group_name: \"" << group_name
              << "\", updtime: \"" << updtime
              << "\", describe: \"" << describe
              << "\", groupid: " << groupid
              << " }" << std::endl;
}

std::map<std::string, std::string> CALLEDMENT::to_map() const {
    std::map<std::string, std::string> result;
    result["ID"] = std::to_string(id);
    result["CALLEDGT"] = calledgt;
    result["ACTION"] = action;
    result["USERNAME"] = username;
    result["GROUP"] = group_name;
    result["UPDTIME"] = updtime;
    result["DESCRIBE"] = describe;
    result["GROUPID"] = std::to_string(groupid);
    return result;
}