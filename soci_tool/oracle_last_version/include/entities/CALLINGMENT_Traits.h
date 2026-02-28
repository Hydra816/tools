#ifndef CALLINGMENT_TRAITS_H
#define CALLINGMENT_TRAITS_H

#include "TableTraits.h"
#include "CALLINGMENT.h"
#include "SafeGet.h"

template<>
struct TableTraits<CALLINGMENT> {
    static std::string sql() {
        return "SELECT ID, CALLINGT, ACTION, USERNAME, \"GROUP\", UPDTIME, DESCRIBE, GROUPID FROM CALLINGMENT";
    }

    static CALLINGMENT from_row(const soci::row& r) {
        CALLINGMENT obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.callingt = SafeGet::get_string(r, "CALLINGT", "");
        obj.action = SafeGet::get_string(r, "ACTION", "");
        obj.username = SafeGet::get_string(r, "USERNAME", "");
        obj.group_name = SafeGet::get_string(r, "GROUP", "");
        obj.updtime = SafeGet::get_string(r, "UPDTIME", "");
        obj.describe = SafeGet::get_string(r, "DESCRIBE", "");
        obj.groupid = SafeGet::get_long_long(r, "GROUPID", 0);
        return obj;
    }
};

#endif // CALLINGMENT_TRAITS_H