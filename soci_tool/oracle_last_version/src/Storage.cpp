#include "../include/oracle_db/Storage.h"
#include <iostream>

// 静态实例获取
Storage& Storage::instance() {
    static Storage s;
    return s;
}

// 模板类的实现需要在cpp文件中特化或显式实例化
// 这里为每个具体类型提供Model的实现

// 需要在每个实体的cpp文件中特化这些模板方法
// 例如，在FAKEGUARD.cpp中：
// template<>
// std::vector<std::map<std::string, std::string>> Storage::Model<FAKEGUARD>::to_result_map() const {
//     std::vector<std::map<std::string, std::string>> result;
//     result.reserve(data.size());
//     
//     for (const auto& entity : data) {
//         result.push_back(entity.to_map());
//     }
//     
//     return result;
// }

// 通用方法实现
std::vector<std::map<std::string, std::string>> Storage::get_result_map_by_type(const std::string& type_name) {
    for (const auto& [key, ptr] : storage) {
        if (key.name() == type_name) {
            return ptr->to_result_map();
        }
    }
    throw std::runtime_error("未找到类型: " + type_name);
}

std::vector<std::string> Storage::get_all_table_names() const {
    std::vector<std::string> names;
    names.reserve(storage.size());
    
    for (const auto& [key, ptr] : storage) {
        names.push_back(key.name());
    }
    
    return names;
}

size_t Storage::table_count() const {
    return storage.size();
}

size_t Storage::get_data_size_by_type(const std::string& type_name) const {
    for (const auto& [key, ptr] : storage) {
        if (key.name() == type_name) {
            return ptr->get_data_size();
        }
    }
    return 0;
}

void Storage::clear() {
    storage.clear();
    std::cout << "[存储] 已清空所有数据" << std::endl;
}