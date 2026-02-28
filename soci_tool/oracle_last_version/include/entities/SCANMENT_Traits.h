#ifndef SCANMENT_TRAITS_H
#define SCANMENT_TRAITS_H

#include "TableTraits.h"
#include "SCANMENT.h"
#include "SafeGet.h"

template<>
struct TableTraits<SCANMENT> {
    static std::string sql() {
        return "SELECT ID, MONUM, RESET, BLKDUR, USERNAME, UPDTIME, DESCRIBE FROM IOH_TEST.SCANMENT";
    }

    static SCANMENT from_row(const soci::row& r) {
        SCANMENT obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.monum = SafeGet::get_string(r, "MONUM", "");
        obj.reset = SafeGet::get_string(r, "RESET", "");
        obj.blkdur = SafeGet::get_string(r, "BLKDUR", "");
        obj.username = SafeGet::get_string(r, "USERNAME", "");
        obj.updtime = SafeGet::get_string(r, "UPDTIME", "");
        obj.describe = SafeGet::get_string(r, "DESCRIBE", "");
        return obj;
    }
};

#endif // SCANMENT_TRAITS_H