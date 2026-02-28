#ifndef SPOOFMENT_TRAITS_H
#define SPOOFMENT_TRAITS_H

#include "TableTraits.h"
#include "SPOOFMENT.h"
#include "SafeGet.h"

template<>
struct TableTraits<SPOOFMENT> {
    static std::string sql() {
        return "SELECT ID, PREFIX, USERNAME, UPDTIME, DESCRIBE FROM SPOOFMENT";
    }

    static SPOOFMENT from_row(const soci::row& r) {
        SPOOFMENT obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.prefix = SafeGet::get_string(r, "PREFIX", "");
        obj.username = SafeGet::get_string(r, "USERNAME", "");
        obj.updtime = SafeGet::get_string(r, "UPDTIME", "");
        obj.describe = SafeGet::get_string(r, "DESCRIBE", "");
        return obj;
    }
};

#endif // SPOOFMENT_TRAITS_H