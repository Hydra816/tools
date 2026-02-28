#ifndef SWITCHMENT_TRAITS_H
#define SWITCHMENT_TRAITS_H

#include "TableTraits.h"
#include "SWITCHMENT.h"
#include "SafeGet.h"

template<>
struct TableTraits<SWITCHMENT> {
    static std::string sql() {
        return "SELECT ID, CALLINGGTENB, SGTMISBLKENB, SGTBLKNUM, SGTBLKTIME, SGTBLKTTYPE, "
               "SGTWHINUM, SGTWHITIME, SGTWHITTYPE, CALLEDGTENB, DGTBLKNUM, DGTBLKTIME, "
               "DGTBLKTTYPE, DGTWHINUM, DGTWHITIME, DGTWHITTYPE, SMSCGTENB, SMGTBLKNUM, "
               "SMGTBLKTIME, SMGTBLKTTYPE, SMGTWHINUM, SMGTWHITIME, SMGTWHITTYPE, IMSIENB, "
               "IMSIBLKNUM, IMSIBLKTIME, IMSIBLKTTYPE, IMSIWHINUM, IMSIWHITIME, IMSIWHITTYPE, "
               "MAPENB, MAPBLKNUM, MAPBLKTIME, MAPBLKTTYPE, MAPWHINUM, MAPWHITIME, MAPWHITTYPE, "
               "MATCHENB, MATCHBLKNUM, MATCHBLKTIME, MATCHBLKTTYPE, MATCHWHINUM, MATCHWHITIME, "
               "MATCHWHITTYPE, FAKEENB, FAKESRIVP, FAKENUM, FAKETIME, FAKETTYPE, SPOOFENB, "
               "SPOOFBLKNUM, SPOOFBLKTIME, SPOOFBLKTTYPE, HOMEROUTENB, HOMELOCGT, HOMECACHEVP, "
               "SCANENB, SCANNUM, SCANTIME, SCANTTYPE, FLOODENB, MTSPOOFENB, MTSPOOFBLKNUM, "
               "MTSPOOFBLKTIME, MTSPOOFBLKTTYPE FROM IOH_TEST.SWITCHMENT";
    }

    static SWITCHMENT from_row(const soci::row& r) {
        SWITCHMENT obj;
        obj.id = SafeGet::get_long_long(r, "ID", 0);
        obj.callinggtenb = SafeGet::get_string(r, "CALLINGGTENB", "");
        obj.sgtmisblkenb = SafeGet::get_string(r, "SGTMISBLKENB", "");
        obj.sgtblknum = SafeGet::get_string(r, "SGTBLKNUM", "");
        obj.sgtblktime = SafeGet::get_string(r, "SGTBLKTIME", "");
        obj.sgtblktype = SafeGet::get_string(r, "SGTBLKTTYPE", "");
        obj.sgtwhinum = SafeGet::get_string(r, "SGTWHINUM", "");
        obj.sgtwhitime = SafeGet::get_string(r, "SGTWHITIME", "");
        obj.sgtwhitype = SafeGet::get_string(r, "SGTWHITTYPE", "");
        obj.calledgtenb = SafeGet::get_string(r, "CALLEDGTENB", "");
        obj.dgtblknum = SafeGet::get_string(r, "DGTBLKNUM", "");
        obj.dgtblktime = SafeGet::get_string(r, "DGTBLKTIME", "");
        obj.dgtblktype = SafeGet::get_string(r, "DGTBLKTTYPE", "");
        obj.dgtwhinum = SafeGet::get_string(r, "DGTWHINUM", "");
        obj.dgtwhitime = SafeGet::get_string(r, "DGTWHITIME", "");
        obj.dgtwhitype = SafeGet::get_string(r, "DGTWHITTYPE", "");
        obj.smscgtenb = SafeGet::get_string(r, "SMSCGTENB", "");
        obj.smgtblknum = SafeGet::get_string(r, "SMGTBLKNUM", "");
        obj.smgtblktime = SafeGet::get_string(r, "SMGTBLKTIME", "");
        obj.smgtblktype = SafeGet::get_string(r, "SMGTBLKTTYPE", "");
        obj.smgtwhinum = SafeGet::get_string(r, "SMGTWHINUM", "");
        obj.smgtwhitime = SafeGet::get_string(r, "SMGTWHITIME", "");
        obj.smgtwhitype = SafeGet::get_string(r, "SMGTWHITTYPE", "");
        obj.imsienb = SafeGet::get_string(r, "IMSIENB", "");
        obj.imsiblknum = SafeGet::get_string(r, "IMSIBLKNUM", "");
        obj.imsiblktime = SafeGet::get_string(r, "IMSIBLKTIME", "");
        obj.imsiblktype = SafeGet::get_string(r, "IMSIBLKTTYPE", "");
        obj.imsiwhinum = SafeGet::get_string(r, "IMSIWHINUM", "");
        obj.imsiwhitime = SafeGet::get_string(r, "IMSIWHITIME", "");
        obj.imsiwhitype = SafeGet::get_string(r, "IMSIWHITTYPE", "");
        obj.mapenb = SafeGet::get_string(r, "MAPENB", "");
        obj.mapblknum = SafeGet::get_string(r, "MAPBLKNUM", "");
        obj.mapblktime = SafeGet::get_string(r, "MAPBLKTIME", "");
        obj.mapblktype = SafeGet::get_string(r, "MAPBLKTTYPE", "");
        obj.mapwhinum = SafeGet::get_string(r, "MAPWHINUM", "");
        obj.mapwhitime = SafeGet::get_string(r, "MAPWHITIME", "");
        obj.mapwhitype = SafeGet::get_string(r, "MAPWHITTYPE", "");
        obj.matchenb = SafeGet::get_string(r, "MATCHENB", "");
        obj.matchblknum = SafeGet::get_string(r, "MATCHBLKNUM", "");
        obj.matchblktime = SafeGet::get_string(r, "MATCHBLKTIME", "");
        obj.matchblktype = SafeGet::get_string(r, "MATCHBLKTTYPE", "");
        obj.matchwhinum = SafeGet::get_string(r, "MATCHWHINUM", "");
        obj.matchwhitime = SafeGet::get_string(r, "MATCHWHITIME", "");
        obj.matchwhitype = SafeGet::get_string(r, "MATCHWHITTYPE", "");
        obj.fakeenb = SafeGet::get_string(r, "FAKEENB", "");
        obj.fakesrivp = SafeGet::get_string(r, "FAKESRIVP", "");
        obj.fakenum = SafeGet::get_string(r, "FAKENUM", "");
        obj.faketime = SafeGet::get_string(r, "FAKETIME", "");
        obj.faketype = SafeGet::get_string(r, "FAKETTYPE", "");
        obj.spoofenb = SafeGet::get_string(r, "SPOOFENB", "");
        obj.spoofblknum = SafeGet::get_string(r, "SPOOFBLKNUM", "");
        obj.spoofblktime = SafeGet::get_string(r, "SPOOFBLKTIME", "");
        obj.spoofblktype = SafeGet::get_string(r, "SPOOFBLKTTYPE", "");
        obj.homerouteenb = SafeGet::get_string(r, "HOMEROUTENB", "");
        obj.homelocgt = SafeGet::get_string(r, "HOMELOCGT", "");
        obj.homecachevp = SafeGet::get_string(r, "HOMECACHEVP", "");
        obj.scanenb = SafeGet::get_string(r, "SCANENB", "");
        obj.scannum = SafeGet::get_string(r, "SCANNUM", "");
        obj.scantime = SafeGet::get_string(r, "SCANTIME", "");
        obj.scanttype = SafeGet::get_string(r, "SCANTTYPE", "");
        obj.floodenb = SafeGet::get_string(r, "FLOODENB", "");
        obj.mtspoofenb = SafeGet::get_string(r, "MTSPOOFENB", "");
        obj.mtspoofblknum = SafeGet::get_string(r, "MTSPOOFBLKNUM", "");
        obj.mtspoofblktime = SafeGet::get_string(r, "MTSPOOFBLKTIME", "");
        obj.mtspoofblktype = SafeGet::get_string(r, "MTSPOOFBLKTTYPE", "");
        return obj;
    }
};

#endif // SWITCHMENT_TRAITS_H