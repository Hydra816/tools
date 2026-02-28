#ifndef FAKEMENT_TRAITS_H
#define FAKEMENT_TRAITS_H

#include "TableTraits.h"
#include "FAKEMENT.h"
#include "SafeGet.h"

template<>
struct TableTraits<FAKEMENT> {
    static std::string sql() {
        return "SELECT ID, SMSCGT, MAXNUM, USERNAME, UPDTIME, DESCRIBE FROM FAKEMENT";
    }

    static FAKEMENT from_row(const soci::row& r) {
        FAKEMENT obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.smscgt = SafeGet::get_string(r, "SMSCGT", "");
        obj.maxnum = SafeGet::get_string(r, "MAXNUM", "");
        obj.username = SafeGet::get_string(r, "USERNAME", "");
        obj.updtime = SafeGet::get_string(r, "UPDTIME", "");
        obj.describe = SafeGet::get_string(r, "DESCRIBE", "");
        return obj;
    }
};

#endif // FAKEMENT_TRAITS_H