#include "ROUTINGROUP.h"
#include <iostream>
#include <sstream>

void ROUTINGROUP::print() const {
    std::cout << "ROUTINGROUP { id: " << id 
              << ", sccpgt: \"" << sccpgt
              << "\", groupid: " << groupid
              << ", updtime: \"" << updtime
              << "\", username: \"" << username
              << "\", group_name: \"" << group_name
              << "\" }" << std::endl;
}

std::map<std::string, std::string> ROUTINGROUP::to_map() const {
    std::map<std::string, std::string> result;
    result["ID"] = std::to_string(id);
    result["SCCPGT"] = sccpgt;
    result["GROUPID"] = std::to_string(groupid);
    result["UPDTIME"] = updtime;
    result["USERNAME"] = username;
    result["GROUP"] = group_name;  // 保持与数据库一致
    return result;
}