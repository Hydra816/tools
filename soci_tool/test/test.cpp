#include "OracleManager.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
//ps:这个测试代码编译出可执行程序后要手动加载oracle环境变量 否则会出现 terminate called after throwing an instance of 'soci::soci_error'
//what():  Cannot create environment
//Aborted (core dumped) 的报错
int main(){
    std::string connection_string = 
        "service=//10.14.65.21:15216/ORCL_UTF8 user=ioh_test password=wacos1234"; 
        
    OracleManager::getInstance().init(connection_string);

    vector<string> names = OracleManager::getInstance().GetAllTableNames();
    std::cout << "所有表名：" << std::endl;
    for(auto name : names){
        std::cout << name << std::endl;
    }
    vector<map<string, string> > resultMap;
    if(!OracleManager::getInstance().GetResultFromTableName<FAKEGUARD>(resultMap)){
        std::cout << "查询失败" << std::endl;
    }
}
