#include "SMSCMENT.h"
#include <iostream>
#include <sstream>

void SMSCMENT::print() const {
    std::cout << "SMSCMENT { id: " << id 
              << ", smscgt: \"" << smscgt
              << "\", msgty: \"" << msgty
              << "\", action: \"" << action
              << "\", username: \"" << username
              << "\", group_name: \"" << group_name
              << "\", updtime: \"" << updtime
              << "\", describe: \"" << describe
              << "\", groupid: " << groupid
              << " }" << std::endl;
}

std::map<std::string, std::string> SMSCMENT::to_map() const {
    std::map<std::string, std::string> result;
    result["ID"] = std::to_string(id);
    result["SMSCGT"] = smscgt;
    result["MSGTY"] = msgty;
    result["ACTION"] = action;
    result["USERNAME"] = username;
    result["GROUP"] = group_name;
    result["UPDTIME"] = updtime;
    result["DESCRIBE"] = describe;
    result["GROUPID"] = std::to_string(groupid);
    return result;
}