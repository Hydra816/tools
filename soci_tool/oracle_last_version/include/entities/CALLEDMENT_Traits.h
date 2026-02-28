#ifndef CALLEDMENT_TRAITS_H
#define CALLEDMENT_TRAITS_H

#include "TableTraits.h"
#include "CALLEDMENT.h"
#include "SafeGet.h"

template<>
struct TableTraits<CALLEDMENT> {
    static std::string sql() {
        return "SELECT ID, CALLEDGT, ACTION, USERNAME, \"GROUP\", UPDTIME, DESCRIBE, GROUPID FROM CALLEDMENT";
    }

    static CALLEDMENT from_row(const soci::row& r) {
        CALLEDMENT obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.calledgt = SafeGet::get_string(r, "CALLEDGT", "");
        obj.action = SafeGet::get_string(r, "ACTION", "");
        obj.username = SafeGet::get_string(r, "USERNAME", "");
        obj.group_name = SafeGet::get_string(r, "GROUP", "");
        obj.updtime = SafeGet::get_string(r, "UPDTIME", "");
        obj.describe = SafeGet::get_string(r, "DESCRIBE", "");
        obj.groupid = SafeGet::get_long_long(r, "GROUPID", 0);
        return obj;
    }
};

#endif // CALLEDMENT_TRAITS_H