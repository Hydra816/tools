#ifndef MAPMENT_TRAITS_H
#define MAPMENT_TRAITS_H

#include "TableTraits.h"
#include "MAPMENT.h"
#include "SafeGet.h"

template<>
struct TableTraits<MAPMENT> {
    static std::string sql() {
        return "SELECT ID, GT, COUNTRY, OPENUM, ACTION, USERNAME, UPDTIME, DESCRIBE FROM IOH_TEST.MAPMENT";
    }

    static MAPMENT from_row(const soci::row& r) {
        MAPMENT obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.gt = SafeGet::get_string(r, "GT", "");
        obj.country = SafeGet::get_string(r, "COUNTRY", "");
        obj.openum = SafeGet::get_string(r, "OPENUM", "");
        obj.action = SafeGet::get_string(r, "ACTION", "");
        obj.username = SafeGet::get_string(r, "USERNAME", "");
        obj.updtime = SafeGet::get_string(r, "UPDTIME", "");
        obj.describe = SafeGet::get_string(r, "DESCRIBE", "");
        return obj;
    }
};

#endif // MAPMENT_TRAITS_H