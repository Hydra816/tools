#ifndef SMSCMENT_TRAITS_H
#define SMSCMENT_TRAITS_H

#include "TableTraits.h"
#include "SMSCMENT.h"
#include "SafeGet.h"

template<>
struct TableTraits<SMSCMENT> {
    static std::string sql() {
        return "SELECT ID, SMSCGT, MSGTY, \"ACTION\", USERNAME, \"GROUP\", UPDTIME, \"DESCRIBE\", GROUPID FROM SMSCMENT";
    }

    static SMSCMENT from_row(const soci::row& r) {
        SMSCMENT obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.smscgt = SafeGet::get_string(r, "SMSCGT", "");
        obj.msgty = SafeGet::get_string(r, "MSGTY", "");
        obj.action = SafeGet::get_string(r, "ACTION", "");
        obj.username = SafeGet::get_string(r, "USERNAME", "");
        obj.group_name = SafeGet::get_string(r, "GROUP", "");
        obj.updtime = SafeGet::get_string(r, "UPDTIME", "");
        obj.describe = SafeGet::get_string(r, "DESCRIBE", "");
        obj.groupid = SafeGet::get_long_long(r, "GROUPID", 0);
        return obj;
    }
};

#endif // SMSCMENT_TRAITS_H