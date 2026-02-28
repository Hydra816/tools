#include "../include/oracle_db/SafeGet.h"
#include <iostream>

namespace SafeGet {
    
    bool has_column(const soci::row& r, const std::string& col_name) {
        try {
            r.get_indicator(col_name);
            return true;
        } catch (...) {
            return false;
        }
    }
    
    long long get_long_long(const soci::row& r, const std::string& col_name, long long default_val) {
        try {
            soci::indicator ind = r.get_indicator(col_name);
            if (ind == soci::i_ok) {
                return r.get<long long>(col_name);
            } else if (ind == soci::i_null) {
                return default_val;
            }
        } catch (const soci::soci_error& e) {
            std::cerr << "字段 " << col_name << " 不存在或类型不匹配: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "获取字段 " << col_name << " 错误: " << e.what() << std::endl;
        }
        return default_val;
    }
    
    int get_int(const soci::row& r, const std::string& col_name, int default_val) {
        try {
            soci::indicator ind = r.get_indicator(col_name);
            if (ind == soci::i_ok) {
                return r.get<int>(col_name);
            } else if (ind == soci::i_null) {
                return default_val;
            }
        } catch (const soci::soci_error& e) {
            std::cerr << "字段 " << col_name << " 不存在或类型不匹配: " << e.what() << std::endl;
        }
        return default_val;
    }
    
    double get_double(const soci::row& r, const std::string& col_name, double default_val) {
        try {
            soci::indicator ind = r.get_indicator(col_name);
            if (ind == soci::i_ok) {
                return r.get<double>(col_name);
            } else if (ind == soci::i_null) {
                return default_val;
            }
        } catch (const soci::soci_error& e) {
            std::cerr << "字段 " << col_name << " 不存在或类型不匹配: " << e.what() << std::endl;
        }
        return default_val;
    }
    
    std::string get_string(const soci::row& r, const std::string& col_name, const std::string& default_val) {
        try {
            soci::indicator ind = r.get_indicator(col_name);
            if (ind == soci::i_ok) {
                return r.get<std::string>(col_name);
            } else if (ind == soci::i_null) {
                return default_val;
            }
        } catch (const soci::soci_error& e) {
            std::cerr << "字段 " << col_name << " 不存在或类型不匹配: " << e.what() << std::endl;
        }
        return default_val;
    }
}