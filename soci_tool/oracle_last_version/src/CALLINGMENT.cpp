#include "CALLINGMENT.h"
#include <iostream>
#include <sstream>

void CALLINGMENT::print() const {
    std::cout << "CALLINGMENT { id: " << id 
              << ", callingt: \"" << callingt
              << "\", action: \"" << action
              << "\", username: \"" << username
              << "\", group_name: \"" << group_name
              << "\", updtime: \"" << updtime
              << "\", describe: \"" << describe
              << "\", groupid: " << groupid
              << " }" << std::endl;
}

std::map<std::string, std::string> CALLINGMENT::to_map() const {
    std::map<std::string, std::string> result;
    result["ID"] = std::to_string(id);
    result["CALLINGT"] = callingt;
    result["ACTION"] = action;
    result["USERNAME"] = username;
    result["GROUP"] = group_name;
    result["UPDTIME"] = updtime;
    result["DESCRIBE"] = describe;
    result["GROUPID"] = std::to_string(groupid);
    return result;
}