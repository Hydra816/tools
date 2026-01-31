#ifndef FAKEGUARD_TRAITS_H
#define FAKEGUARD_TRAITS_H

#include "../oracle_db/TableTraits.h"
#include "FAKEGUARD.h"
#include "../oracle_db/SafeGet.h"

// ================= FAKEGUARD Traits特化 =================
template<>
struct TableTraits<FAKEGUARD> {
    static std::string sql() {
        return "SELECT ID, GTPREFIX, DESCRIBE, UPDTIME, USERNAME FROM FAKEGUARD";
    }

    static FAKEGUARD from_row(const soci::row& r) {
        FAKEGUARD obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.gtprefix = SafeGet::get_string(r, "GTPREFIX", "");
        obj.describe = SafeGet::get_string(r, "DESCRIBE", "");
        obj.updatetime = SafeGet::get_string(r, "UPDTIME", "");
        obj.username = SafeGet::get_string(r, "USERNAME", "");
        return obj;
    }
};

#endif // FAKEGUARD_TRAITS_H