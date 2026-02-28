#include "SRILOOP.h"
#include <iostream>
#include <sstream>

void SRILOOP::print() const {
    std::cout << "SRILOOP { id: " << id 
              << ", detectedtime: " << detectedtime
              << ", detectednums: " << detectednums
              << ", sriloopenb: " << sriloopenb
              << " }" << std::endl;
}

std::map<std::string, std::string> SRILOOP::to_map() const {
    std::map<std::string, std::string> result;
    result["ID"] = std::to_string(id);
    result["DETECTEDTIME"] = std::to_string(detectedtime);
    result["DETECTEDNUMS"] = std::to_string(detectednums);
    result["SRILOOPENB"] = std::to_string(sriloopenb);
    return result;
}