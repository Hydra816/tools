#include "../include/oracle_db/TableLoader.h"
#include "../include/oracle_db/SafeGet.h"
#include <iostream>
#include <chrono>

std::vector<std::map<std::string, std::string>> TableLoader::dynamic_query(
    soci::session& sql,
    const std::string& table_name,
    const std::string& where_clause,
    const std::vector<std::string>& columns) {
    
    std::vector<std::map<std::string, std::string>> result;
    
    try {
        // 构建SQL语句
        std::string sql_str = "SELECT ";
        
        if (columns.empty()) {
            sql_str += "*";
        } else {
            for (size_t i = 0; i < columns.size(); ++i) {
                sql_str += columns[i];
                if (i < columns.size() - 1) {
                    sql_str += ", ";
                }
            }
        }
        
        sql_str += " FROM " + table_name;
        
        if (!where_clause.empty()) {
            sql_str += " " + where_clause;
        }
        
        std::cout << "[动态查询] 执行SQL: " << sql_str << std::endl;
        auto start = std::chrono::steady_clock::now();
        
        soci::rowset<soci::row> rs = (sql.prepare << sql_str);
        int row_count = 0;
        
        // 获取列信息（只在第一行时获取）
        std::vector<std::string> column_names;
        bool first_row = true;
        
        for (auto& r : rs) {
            if (first_row) {
                // 获取所有列名
                std::size_t col_count = r.size();
                for (std::size_t i = 0; i < col_count; ++i) {
                    column_names.push_back(r.get_properties(i).get_name());
                }
                first_row = false;
            }
            
            // 构建一行数据
            std::map<std::string, std::string> row_data;
            for (const auto& col_name : column_names) {
                std::string value = SafeGet::get_string(r, col_name, "");
                row_data[col_name] = value;
            }
            
            result.push_back(std::move(row_data));
            row_count++;
            
            // 每100条记录打印一次进度
            if (row_count % 100 == 0) {
                std::cout << "[动态查询] 进度: 已加载 " << row_count << " 行" << std::endl;
            }
        }
        
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "[动态查询] 完成: " << table_name 
                  << ", 行数: " << row_count
                  << ", 耗时: " << duration.count() << "ms" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "[动态查询] 执行SQL失败: " << e.what() << std::endl;
        throw;
    }
    
    return result;
}