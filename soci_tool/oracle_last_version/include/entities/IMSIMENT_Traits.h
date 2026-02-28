#ifndef IMSIMENT_TRAITS_H
#define IMSIMENT_TRAITS_H

#include "TableTraits.h"
#include "IMSIMENT.h"
#include "SafeGet.h"

template<>
struct TableTraits<IMSIMENT> {
    static std::string sql() {
        return "SELECT ID, IMSI, ACTION, USERNAME, \"GROUP\", UPDTIME, DESCRIBE, GROUPID FROM IMSIMENT";
    }

    static IMSIMENT from_row(const soci::row& r) {
        IMSIMENT obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.imsi = SafeGet::get_string(r, "IMSI", "");
        obj.action = SafeGet::get_string(r, "ACTION", "");
        obj.username = SafeGet::get_string(r, "USERNAME", "");
        obj.group_name = SafeGet::get_string(r, "GROUP", "");
        obj.updtime = SafeGet::get_string(r, "UPDTIME", "");
        obj.describe = SafeGet::get_string(r, "DESCRIBE", "");
        obj.groupid = SafeGet::get_long_long(r, "GROUPID", 0);
        return obj;
    }
};

#endif // IMSIMENT_TRAITS_H