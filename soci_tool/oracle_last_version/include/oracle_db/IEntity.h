#ifndef IENTITY_H
#define IENTITY_H

#include <string>
#include <map>

// ================= 基础接口 =================
struct IEntity {
    virtual ~IEntity() = default;
    virtual std::string name() const = 0;
    virtual void print() const = 0;  // 打印
    
    // 转换为map的接口
    virtual std::map<std::string, std::string> to_map() const = 0;
};

#endif // IENTITY_H
