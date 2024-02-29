#include "ServerInfo.h"

ProbeMsgResponse PrepareProbeMatchData(int id, bool match, std::string& serverName) {
    ProbeMsgResponse probe;
    probe.set_medicalserverid(id);
    probe.set_medicalservername(serverName);
    probe.set_probematch(match);
    return probe;
}
