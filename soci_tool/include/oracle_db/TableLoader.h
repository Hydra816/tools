#ifndef TABLE_LOADER_H
#define TABLE_LOADER_H

#include <soci/soci.h>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <iostream>
#include "TableTraits.h"
#include "SafeGet.h"

// ================= 通用 Loader =================
class TableLoader {
public:
    template<typename T>
    static std::vector<T> load(soci::session& sql);
    
    // 动态查询接口
    static std::vector<std::map<std::string, std::string>> dynamic_query(
        soci::session& sql,
        const std::string& table_name,
        const std::string& where_clause = "",
        const std::vector<std::string>& columns = {});
};

// 模板方法实现
template<typename T>
std::vector<T> TableLoader::load(soci::session& sql) {
    std::vector<T> result;
    int success_count = 0;
    int error_count = 0;
    
    try {
        std::cout << "[加载] 开始执行SQL: " << TableTraits<T>::sql() << std::endl;
        auto start = std::chrono::steady_clock::now();
        
        soci::rowset<soci::row> rs = (sql.prepare << TableTraits<T>::sql());
        
        for (auto& r : rs) {
            try {
                T obj = TableTraits<T>::from_row(r);
                result.push_back(std::move(obj));
                success_count++;
                
                // 每100条记录打印一次进度
                if (success_count % 100 == 0) {
                    std::cout << "[进度] " << typeid(T).name() << " 已加载 " 
                              << success_count << " 条记录" << std::endl;
                }
                
            } catch (const std::exception& e) {
                error_count++;
                std::cerr << "[错误] 转换记录失败 (" << error_count << "): " 
                          << e.what() << std::endl;
                continue;
            }
        }
        
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "[加载] 完成: " << typeid(T).name() 
                  << ", 成功: " << success_count 
                  << ", 失败: " << error_count
                  << ", 耗时: " << duration.count() << "ms" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "[错误] 执行SQL失败: " << e.what() << std::endl;
        throw;
    }
    return result;
}

#endif // TABLE_LOADER_H