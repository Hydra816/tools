#ifndef ROUTINGROUP_TRAITS_H
#define ROUTINGROUP_TRAITS_H

#include "TableTraits.h"
#include "ROUTINGROUP.h"
#include "SafeGet.h"

template<>
struct TableTraits<ROUTINGROUP> {
    static std::string sql() {
        return "SELECT ID, SCCPGT, GROUPID, UPDTIME, USERNAME, \"GROUP\" FROM ROUTINGROUP";
    }

    static ROUTINGROUP from_row(const soci::row& r) {
        ROUTINGROUP obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.sccpgt = SafeGet::get_string(r, "SCCPGT", "");
        obj.groupid = SafeGet::get_long_long(r, "GROUPID", 0);
        obj.updtime = SafeGet::get_string(r, "UPDTIME", "");
        obj.username = SafeGet::get_string(r, "USERNAME", "");
        obj.group_name = SafeGet::get_string(r, "GROUP", "");  // 注意这里用双引号
        return obj;
    }
};

#endif // ROUTINGROUP_TRAITS_H