#ifndef TABLE_TRAITS_H
#define TABLE_TRAITS_H

#include <soci/soci.h>
#include <string>

// ================= Traits基类声明 =================
template<typename T>
struct TableTraits {
    static std::string sql();
    static T from_row(const soci::row& r);
};

#endif // TABLE_TRAITS_H