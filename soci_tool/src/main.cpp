#include "../include/oracle_db/Registry.h"
#include "../include/oracle_db/Storage.h"
#include "../include/oracle_db/EntityConverter.h"
#include "../include/entities/FAKEGUARD_Traits.h"
#include <soci/soci.h>
#include <soci/oracle/soci-oracle.h>
#include <iostream>
#include <chrono>

// ================= 自动注册 =================
namespace {
    static bool _reg_fakeguard = [](){
        TableRegistry::register_table<FAKEGUARD>();
        return true;
    }();
}

// ================= 主函数 =================
int main() {
    std::cout << "===== Oracle数据库工具演示 =====" << std::endl;
    
    try {
        // 连接数据库
        std::cout << "\n[连接] 连接到数据库..." << std::endl;
        std::string connection_string = 
            "service=//10.14.65.21:15216/ORCL_UTF8 user=ioh_test password=wacos1234"; 
            
        std::cout << "连接字符串: " << connection_string << std::endl;
        
        soci::session sql(soci::oracle, connection_string);

        // 加载所有表
        TableRegistry::instance().load_all(sql);

        // 演示各种使用方式
        std::cout << "\n[演示] 各种数据访问方式..." << std::endl;
        
        // 1. 原有的方式
        std::cout << "\n1. 原有的get<T>()方式:" << std::endl;
        auto& fakeguards = Storage::instance().get<FAKEGUARD>();
        if (!fakeguards.empty()) {
            std::cout << "获取到 " << fakeguards.size() << " 条记录" << std::endl;
            fakeguards[0].print();
        }
        
        // 2. 转换为resultMap
        std::cout << "\n2. 转换为resultMap:" << std::endl;
        auto result_map = Storage::instance().get_result_map<FAKEGUARD>();
        std::cout << "转换完成，共 " << result_map.size() << " 条记录" << std::endl;
        
        // 3. 使用工具类格式化输出
        if (!result_map.empty()) {
            std::string formatted = EntityConverter::to_string(result_map, 3);
            std::cout << formatted;
        }
        
        // 显示存储信息
        std::cout << "\n[存储信息]" << std::endl;
        std::cout << "已加载表数量: " << Storage::instance().table_count() << std::endl;
        std::cout << "FAKEGUARD表数据量: " << Storage::instance().get_data_size<FAKEGUARD>() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "\n[错误] 程序错误: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n===== 程序执行完成 =====" << std::endl;
    return 0;
}