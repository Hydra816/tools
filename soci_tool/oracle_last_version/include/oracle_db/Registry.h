#ifndef REGISTRY_H
#define REGISTRY_H

#include <functional>
#include <vector>
#include <soci/soci.h>
#include <iostream>
#include "TableLoader.h"
#include "Storage.h"
// ================= 表注册管理器 =================
class TableRegistry {
private:
    std::vector<std::function<void(soci::session&)>> loaders;
    
    TableRegistry() = default;
    TableRegistry(const TableRegistry&) = delete;
    TableRegistry& operator=(const TableRegistry&) = delete;
    
public:
    static TableRegistry& instance();
    
    template<typename T>
    static void register_table();
    
    void load_all(soci::session& sql);
};

// 模板方法实现
template<typename T>
void TableRegistry::register_table() {
    std::cout << "[注册] 注册表: " << typeid(T).name() << std::endl;
    instance().loaders.push_back([](soci::session& sql){
        try {
            auto data = TableLoader::load<T>(sql);
            Storage::instance().store<T>(std::move(data));
        } catch (const std::exception& e) {
            std::cerr << "[注册] 加载表失败: " << e.what() << std::endl;
        }
    });
}

#endif // REGISTRY_H