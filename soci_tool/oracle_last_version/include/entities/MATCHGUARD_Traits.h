#ifndef MATCHGUARD_TRAITS_H
#define MATCHGUARD_TRAITS_H

#include "TableTraits.h"
#include "MATCHGUARD.h"
#include "SafeGet.h"

template<>
struct TableTraits<MATCHGUARD> {
    static std::string sql() {
        return "SELECT ID, NAME, DESCRIBE, ACTION, GTSMSCMISMATCH, SIDGTMISMATCH, "
               "SIDSMSCMISMATCH, SENDERIDTYPE, PHRASEDATAENCODING, MESSAGETYPE, "
               "SRILOOPDETECTED, CALLINGGT, SMSCGT, IMSI, PHRASE, WEIGHTEDKEYWORS, "
               "SID, RID, UPDTIME, USERNAME FROM MATCHGUARD";
    }

    static MATCHGUARD from_row(const soci::row& r) {
        MATCHGUARD obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.name_ = SafeGet::get_string(r, "NAME", "");
        obj.describe = SafeGet::get_string(r, "DESCRIBE", "");
        obj.action = SafeGet::get_long_long(r, "ACTION", 0);
        obj.gtsmscmismatch = SafeGet::get_long_long(r, "GTSMSCMISMATCH", 0);
        obj.sidgtmismatch = SafeGet::get_long_long(r, "SIDGTMISMATCH", 0);
        obj.sidsmscmismatch = SafeGet::get_long_long(r, "SIDSMSCMISMATCH", 0);
        obj.senderidtype = SafeGet::get_long_long(r, "SENDERIDTYPE", 0);
        obj.phrasedataencoding = SafeGet::get_long_long(r, "PHRASEDATAENCODING", 0);
        obj.messagetype = SafeGet::get_long_long(r, "MESSAGETYPE", 0);
        obj.sriloopdetected = SafeGet::get_long_long(r, "SRILOOPDETECTED", 0);
        obj.callinggt = SafeGet::get_string(r, "CALLINGGT", "");
        obj.smscgt = SafeGet::get_string(r, "SMSCGT", "");
        obj.imsi = SafeGet::get_string(r, "IMSI", "");
        obj.phrase = SafeGet::get_string(r, "PHRASE", "");
        obj.weightedkeywors = SafeGet::get_string(r, "WEIGHTEDKEYWORS", "");
        obj.sid = SafeGet::get_string(r, "SID", "");
        obj.rid = SafeGet::get_string(r, "RID", "");
        obj.updtime = SafeGet::get_string(r, "UPDTIME", "");
        obj.username = SafeGet::get_string(r, "USERNAME", "");
        return obj;
    }
};

#endif // MATCHGUARD_TRAITS_H