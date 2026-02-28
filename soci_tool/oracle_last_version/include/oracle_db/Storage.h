#ifndef STORAGE_H
#define STORAGE_H

#include <unordered_map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "IEntity.h"

// ================= Storage 单例 =================
class Storage {
private:
    struct Base { 
        virtual ~Base() = default; 
        virtual std::vector<std::map<std::string, std::string>> to_result_map() const = 0;
        virtual size_t get_data_size() const = 0;
        virtual std::string get_type_name() const = 0;
    };

    template<typename T>
    struct Model : Base {
        std::vector<T> data;
        Model(std::vector<T>&& d) : data(std::move(d)) {}
        
        // 实现虚函数：转换为result_map
        std::vector<std::map<std::string, std::string>> to_result_map() const override {
            std::vector<std::map<std::string, std::string>> result;
            result.reserve(data.size());
            
            for (const auto& entity : data) {
                result.push_back(entity.to_map());
            }
            
            return result;
        }
        
        // 获取数据大小
        size_t get_data_size() const override {
            return data.size();
        }
        
        // 获取类型名
        std::string get_type_name() const override {
            return typeid(T).name();
        }
    };

    std::unordered_map<std::type_index, std::shared_ptr<Base>> storage;
    
    Storage() = default;
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;
    
public:
    static Storage& instance();
    
    template<typename T>
    void store(std::vector<T>&& data);
    
    template<typename T>
    std::vector<T>& get();
    
    template<typename T>
    std::vector<std::map<std::string, std::string>> get_result_map();
    
    std::vector<std::map<std::string, std::string>> get_result_map_by_type(const std::string& type_name);
    std::vector<std::string> get_all_table_names() const;
    size_t table_count() const;
    
    template<typename T>
    size_t get_data_size() const;
    
    size_t get_data_size_by_type(const std::string& type_name) const;
    void clear();
};

// 模板方法实现
template<typename T>
void Storage::store(std::vector<T>&& data) {
    std::type_index key = typeid(T);
    std::cout << "[存储] 存入: " << typeid(T).name() 
              << ", 记录数: " << data.size() << std::endl;
    storage[key] = std::make_shared<Model<T>>(std::move(data));
}

template<typename T>
std::vector<T>& Storage::get() {
    std::type_index key = typeid(T);
    auto it = storage.find(key);
    if (it == storage.end()) {
        throw std::runtime_error("表未找到: " + std::string(typeid(T).name()));
    }
    
    Model<T>* model = dynamic_cast<Model<T>*>(it->second.get());
    if (!model) {
        throw std::bad_cast();
    }
    
    return model->data;
}

template<typename T>
std::vector<std::map<std::string, std::string>> Storage::get_result_map() {
    auto& data = get<T>();
    std::vector<std::map<std::string, std::string>> result;
    result.reserve(data.size());
    
    for (const auto& entity : data) {
        result.push_back(entity.to_map());
    }
    
    return result;
}

template<typename T>
size_t Storage::get_data_size() const {
    std::type_index key = typeid(T);
    auto it = storage.find(key);
    if (it == storage.end()) {
        return 0;
    }
    return it->second->get_data_size();
}

#endif // STORAGE_H