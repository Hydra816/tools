#ifndef SRILOOP_TRAITS_H
#define SRILOOP_TRAITS_H

#include "TableTraits.h"
#include "SRILOOP.h"
#include "SafeGet.h"

template<>
struct TableTraits<SRILOOP> {
    static std::string sql() {
        return "SELECT ID, DETECTEDTIME, DETECTEDNUMS, SRILOOPENB FROM SRILOOP";
    }

    static SRILOOP from_row(const soci::row& r) {
        SRILOOP obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.detectedtime = SafeGet::get_long_long(r, "DETECTEDTIME", 0);
        obj.detectednums = SafeGet::get_long_long(r, "DETECTEDNUMS", 0);
        obj.sriloopenb = SafeGet::get_long_long(r, "SRILOOPENB", 0);
        return obj;
    }
};

#endif // SRILOOP_TRAITS_H