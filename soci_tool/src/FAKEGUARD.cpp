#include "FAKEGUARD.h"
#include <iostream>
#include <sstream>

void FAKEGUARD::print() const {
    std::cout << "FAKEGUARD { id: " << id 
              << ", gtprefix: \"" << gtprefix
              << "\", describe: \"" << describe
              << "\", updatetime: \"" << updatetime
              << "\", username: \"" << username
              << "\" }" << std::endl;
}

std::map<std::string, std::string> FAKEGUARD::to_map() const {
    std::map<std::string, std::string> result;
    result["ID"] = std::to_string(id);
    result["GTPREFIX"] = gtprefix;
    result["DESCRIBE"] = describe;
    result["UPDTIME"] = updatetime;
    result["USERNAME"] = username;
    return result;
}