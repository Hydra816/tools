#include "IMSIMENT.h"
#include <iostream>
#include <sstream>

void IMSIMENT::print() const {
    std::cout << "IMSIMENT { id: " << id 
              << ", imsi: \"" << imsi
              << "\", action: \"" << action
              << "\", username: \"" << username
              << "\", group_name: \"" << group_name
              << "\", updtime: \"" << updtime
              << "\", describe: \"" << describe
              << "\", groupid: " << groupid
              << " }" << std::endl;
}

std::map<std::string, std::string> IMSIMENT::to_map() const {
    std::map<std::string, std::string> result;
    result["ID"] = std::to_string(id);
    result["IMSI"] = imsi;
    result["ACTION"] = action;
    result["USERNAME"] = username;
    result["GROUP"] = group_name;
    result["UPDTIME"] = updtime;
    result["DESCRIBE"] = describe;
    result["GROUPID"] = std::to_string(groupid);
    return result;
}