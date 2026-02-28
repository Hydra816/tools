#ifndef FLOODMENT_TRAITS_H
#define FLOODMENT_TRAITS_H

#include "TableTraits.h"
#include "FLOODMENT.h"
#include "SafeGet.h"

template<>
struct TableTraits<FLOODMENT> {
    static std::string sql() {
        return "SELECT ID, CATEGORY, PARAMTER, MAPLIMIT, OBEYGLOBAL, USERNAME, UPDTIME, DESCRIBE FROM IOH_TEST.FLOODMENT";
    }

    static FLOODMENT from_row(const soci::row& r) {
        FLOODMENT obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.category = SafeGet::get_string(r, "CATEGORY", "");
        obj.paramter = SafeGet::get_string(r, "PARAMTER", "");
        obj.maplimit = SafeGet::get_string(r, "MAPLIMIT", "");
        obj.obeyglobal = SafeGet::get_string(r, "OBEYGLOBAL", "");
        obj.username = SafeGet::get_string(r, "USERNAME", "");
        obj.updtime = SafeGet::get_string(r, "UPDTIME", "");
        obj.describe = SafeGet::get_string(r, "DESCRIBE", "");
        return obj;
    }
};

#endif // FLOODMENT_TRAITS_H