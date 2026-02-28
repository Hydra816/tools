#include "../include/oracle_db/EntityConverter.h"
#include <sstream>
#include <algorithm>

std::string EntityConverter::to_string(const std::vector<std::map<std::string, std::string>>& result_map, size_t limit) {
    if (result_map.empty()) {
        return "Empty result map";
    }
    
    std::ostringstream oss;
    
    // 获取列名
    std::vector<std::string> columns;
    for (const auto& [key, _] : result_map[0]) {
        columns.push_back(key);
    }
    
    // 输出列名
    oss << "Columns: ";
    for (size_t i = 0; i < columns.size(); ++i) {
        oss << columns[i];
        if (i < columns.size() - 1) {
            oss << ", ";
        }
    }
    oss << "\n";
    
    // 输出数据
    size_t display_count = (limit == 0) ? result_map.size() : std::min(limit, result_map.size());
    oss << "Data (" << display_count << " rows):\n";
    
    for (size_t i = 0; i < display_count; ++i) {
        oss << "  Row " << i + 1 << ": ";
        for (size_t j = 0; j < columns.size(); ++j) {
            const auto& col = columns[j];
            auto it = result_map[i].find(col);
            if (it != result_map[i].end()) {
                oss << col << "=" << it->second;
            } else {
                oss << col << "=NULL";
            }
            
            if (j < columns.size() - 1) {
                oss << ", ";
            }
        }
        oss << "\n";
    }
    
    if (limit > 0 && limit < result_map.size()) {
        oss << "  ... and " << (result_map.size() - limit) << " more rows\n";
    }
    
    return oss.str();
}