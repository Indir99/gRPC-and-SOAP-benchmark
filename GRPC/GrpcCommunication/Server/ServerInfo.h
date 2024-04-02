#include <iostream>
#include <myproto/TestFile.pb.h>

ProbeMsgResponse PrepareProbeMatchData(int id, bool match, std::string& serverName);
std::string GetCurrentTime();
void PrepareTherapyData(::TherapyData* thData,
                        std::string patientID,
                        std::string patientFirstName,
                        std::string patientLastName,
                        std::string doctorID,
                        std::string doctorFirstName,
                        std::string doctorLastName,
                        std::string therapyName,
                        std::string therapyStatus);
void PrepareTherapyList(::TherapyList* thList);

struct ServerInformation{
    std::string serverName;
    int serverId;
};

