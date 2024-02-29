#include "ClientInfo.h"

ProbeMsg PrepareProbeData(int id, std::string& clientName, std::string& clientType){
    ProbeMsg probe;
    probe.set_medicaldeviceid(id);
    probe.set_medicaldevicename(clientName);
    probe.set_medicaldevicetype(clientType);
    return probe;
}
