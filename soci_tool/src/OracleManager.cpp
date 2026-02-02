#include "OracleManager.h"
// #include "Registry.h"
// #include "Storage.h"
// #include "EntityConverter.h"
// #include "FAKEGUARD_Traits.h"
#include <soci/soci.h>
#include <soci/oracle/soci-oracle.h>
//todo :提供表名到实例的映射 ,根据ioh原有接口 会传入表名字符串 此时需要转换去调用 Storage::instance().get_result_map<tablename>();
namespace {
    static bool _reg_fakeguard = [](){
        TableRegistry::register_table<FAKEGUARD>();
        return true;
    }();
}

void  OracleManager::init(string conn) {
    std::cout << "\n[连接] 连接到数据库..." << std::endl;        
    std::cout << "连接字符串: " << conn << std::endl;    
    soci::session sql(soci::oracle, conn);
    // 加载所有表
    TableRegistry::instance().load_all(sql);
}


bool OracleManager::GetResultFromTableName(string tableName, 
                                vector< map<string, string> > &resultMap) {
    auto result_map = Storage::instance().get_result_map<FAKEGUARD>();
    //auto result_map = Storage::instance().get_result_map_by_type(tableName);
    std::cout << "转换完成，共 " << result_map.size() << " 条记录" << std::endl;
        
    // 3. 使用工具类格式化输出前三条内容
    if (!result_map.empty()) {
        std::string formatted = EntityConverter::to_string(result_map, 3);
        std::cout << formatted;
        return true;
    }

    return false;   
}

vector<string> OracleManager::GetAllTableNames(){
    return Storage::instance().get_all_table_names();
}