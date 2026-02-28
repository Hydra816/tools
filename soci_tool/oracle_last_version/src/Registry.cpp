#include "../include/oracle_db/Registry.h"
#include "../include/oracle_db/TableLoader.h"
#include "../include/oracle_db/Storage.h"
#include <iostream>

TableRegistry& TableRegistry::instance() {
    static TableRegistry inst;
    return inst;
}

void TableRegistry::load_all(soci::session& sql) {
    std::cout << "\n[系统] 开始加载 " << loaders.size() << " 张表..." << std::endl;
    for (auto& loader : loaders) {
        try {
            loader(sql);
        } catch (const std::exception& e) {
            std::cerr << "[系统] 加载器执行失败: " << e.what() << std::endl;
        }
    }
    std::cout << "[系统] 所有表加载完成" << std::endl;
}