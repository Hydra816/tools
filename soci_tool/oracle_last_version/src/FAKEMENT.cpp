#include "FAKEMENT.h"
#include <iostream>
#include <sstream>

void FAKEMENT::print() const {
    std::cout << "FAKEMENT { id: " << id 
              << ", smscgt: \"" << smscgt
              << "\", maxnum: \"" << maxnum
              << "\", username: \"" << username
              << "\", updtime: \"" << updtime
              << "\", describe: \"" << describe
              << "\" }" << std::endl;
}

std::map<std::string, std::string> FAKEMENT::to_map() const {
    std::map<std::string, std::string> result;
    result["ID"] = std::to_string(id);
    result["SMSCGT"] = smscgt;
    result["MAXNUM"] = maxnum;
    result["USERNAME"] = username;
    result["UPDTIME"] = updtime;
    result["DESCRIBE"] = describe;
    return result;
}