#include "SPOOFMENT.h"
#include <iostream>
#include <sstream>

void SPOOFMENT::print() const {
    std::cout << "SPOOFMENT { id: " << id 
              << ", prefix: \"" << prefix
              << "\", username: \"" << username
              << "\", updtime: \"" << updtime
              << "\", describe: \"" << describe
              << "\" }" << std::endl;
}

std::map<std::string, std::string> SPOOFMENT::to_map() const {
    std::map<std::string, std::string> result;
    result["ID"] = std::to_string(id);
    result["PREFIX"] = prefix;
    result["USERNAME"] = username;
    result["UPDTIME"] = updtime;
    result["DESCRIBE"] = describe;
    return result;
}