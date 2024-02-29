#include <iostream>
#include <myproto/TestFile.pb.h>

ProbeMsgResponse PrepareProbeMatchData(int id, bool match, std::string& serverName);

struct ServerInformation{
    std::string serverName;
    int serverId;
};

