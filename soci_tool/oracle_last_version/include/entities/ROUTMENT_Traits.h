#ifndef ROUTMENT_TRAITS_H
#define ROUTMENT_TRAITS_H

#include "TableTraits.h"
#include "ROUTMENT.h"
#include "SafeGet.h"

template<>
struct TableTraits<ROUTMENT> {
    static std::string sql() {
        return "SELECT ID, PREFIX, USERNAME, UPDTIME, DESCRIBE FROM ROUTMENT";
    }

    static ROUTMENT from_row(const soci::row& r) {
        ROUTMENT obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.prefix = SafeGet::get_string(r, "PREFIX", "");
        obj.username = SafeGet::get_string(r, "USERNAME", "");
        obj.updtime = SafeGet::get_string(r, "UPDTIME", "");
        obj.describe = SafeGet::get_string(r, "DESCRIBE", "");
        return obj;
    }
};

#endif // ROUTMENT_TRAITS_H