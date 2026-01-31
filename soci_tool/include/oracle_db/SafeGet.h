#ifndef SAFE_GET_H
#define SAFE_GET_H

#include <soci/soci.h>
#include <string>

// ================= 安全获取辅助函数 =================
namespace SafeGet {
    
    // 检查字段是否存在
    bool has_column(const soci::row& r, const std::string& col_name);
    
    // 获取 long long 类型
    long long get_long_long(const soci::row& r, const std::string& col_name, long long default_val = 0);
    
    // 获取 int 类型
    int get_int(const soci::row& r, const std::string& col_name, int default_val = 0);
    
    // 获取 double 类型
    double get_double(const soci::row& r, const std::string& col_name, double default_val = 0.0);
    
    // 获取 string 类型
    std::string get_string(const soci::row& r, const std::string& col_name, const std::string& default_val = "");
}

#endif // SAFE_GET_H