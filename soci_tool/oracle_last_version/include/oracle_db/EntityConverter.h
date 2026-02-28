#ifndef ENTITY_CONVERTER_H
#define ENTITY_CONVERTER_H

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

// ================= 转换工具类 =================
class EntityConverter {
public:
    template<typename T>
    static std::vector<std::map<std::string, std::string>> to_result_map(const std::vector<T>& entities);
    
    static std::string to_string(const std::vector<std::map<std::string, std::string>>& result_map, size_t limit = 0);
};

// 模板方法实现
template<typename T>
std::vector<std::map<std::string, std::string>> EntityConverter::to_result_map(const std::vector<T>& entities) {
    std::vector<std::map<std::string, std::string>> result;
    result.reserve(entities.size());
    
    for (const auto& entity : entities) {
        result.push_back(entity.to_map());
    }
    
    return result;
}

#endif // ENTITY_CONVERTER_H