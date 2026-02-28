#include "MATCHGUARD.h"
#include <iostream>
#include <sstream>

void MATCHGUARD::print() const {
    std::cout << "MATCHGUARD { id: " << id 
              << ", name: \"" << name_
              << "\", describe: \"" << describe
              << "\", action: " << action
              << ", gtsmscmismatch: " << gtsmscmismatch
              << ", sidgtmismatch: " << sidgtmismatch
              << ", sidsmscmismatch: " << sidsmscmismatch
              << ", senderidtype: " << senderidtype
              << ", phrasedataencoding: " << phrasedataencoding
              << ", messagetype: " << messagetype
              << ", sriloopdetected: " << sriloopdetected
              << ", callinggt: \"" << callinggt
              << "\", smscgt: \"" << smscgt
              << "\", imsi: \"" << imsi
              << "\", phrase: \"" << phrase
              << "\", weightedkeywors: \"" << weightedkeywors
              << "\", sid: \"" << sid
              << "\", rid: \"" << rid
              << "\", updtime: \"" << updtime
              << "\", username: \"" << username
              << "\" }" << std::endl;
}

std::map<std::string, std::string> MATCHGUARD::to_map() const {
    std::map<std::string, std::string> result;
    result["ID"] = std::to_string(id);
    result["NAME"] = name_;
    result["DESCRIBE"] = describe;
    result["ACTION"] = std::to_string(action);
    result["GTSMSCMISMATCH"] = std::to_string(gtsmscmismatch);
    result["SIDGTMISMATCH"] = std::to_string(sidgtmismatch);
    result["SIDSMSCMISMATCH"] = std::to_string(sidsmscmismatch);
    result["SENDERIDTYPE"] = std::to_string(senderidtype);
    result["PHRASEDATAENCODING"] = std::to_string(phrasedataencoding);
    result["MESSAGETYPE"] = std::to_string(messagetype);
    result["SRILOOPDETECTED"] = std::to_string(sriloopdetected);
    result["CALLINGGT"] = callinggt;
    result["SMSCGT"] = smscgt;
    result["IMSI"] = imsi;
    result["PHRASE"] = phrase;
    result["WEIGHTEDKEYWORS"] = weightedkeywors;
    result["SID"] = sid;
    result["RID"] = rid;
    result["UPDTIME"] = updtime;
    result["USERNAME"] = username;
    return result;
}