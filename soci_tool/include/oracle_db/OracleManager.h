#ifndef __ORACLE_MANAGER_H__
#define __ORACLE_MANAGER_H__
//单例类
//作为本库的对外接口 提供数据库操作接口
//当前仅提供初始化和查询接口

#include <string>
#include <vector>
#include <map>
#include "FAKEGUARD_Traits.h"
#include "Storage.h"
#include "EntityConverter.h"
#include "Registry.h"

using std::string;
using std::vector;
using std::map;

// std::string connection_string = 
//         "service=//10.14.65.21:15216/ORCL_UTF8 user=ioh_test password=wacos1234"; 

class OracleManager
{

public:
    static OracleManager& getInstance(){
        static OracleManager instance;
        return instance;
    }
    //这里面需要调用初始化连接，loadall接口
    void init(string conn);
    bool GetResultFromTableName(string tableName, vector<map<string, string> > &resultMap);
    template<typename T>
    bool GetResultFromTableName(vector<map<string, string> > &resultMap);
    vector<string> GetAllTableNames();
private:
    OracleManager() = default;
    ~OracleManager() = default;
    OracleManager(const OracleManager&) = delete;
    OracleManager& operator=(const OracleManager&) = delete;
};

//实现模板方法
template<typename T>
bool OracleManager::GetResultFromTableName(vector<map<string, string> > &resultMap){
    auto result_map = Storage::instance().get_result_map<T>();
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
#endif // !__ORACLE_MANAGER_H__