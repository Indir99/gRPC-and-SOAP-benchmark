#pragma once

#include <iostream>
#include <myproto/TestFile.pb.h>

constexpr int CLIENT_ID{};
constexpr std::array CLIENT_NAME{"GrpcClientForTesting"};
constexpr std::array CLIENT_TYPE{"RandomType"};

ProbeMsg PrepareProbeData(int id, std::string& clientName, std::string& clientType);
std::string GetCurrentTime();
TherapyData PrepareTherapyData(std::string patientID,
                               std::string patientFirstName,
                               std::string patientLastName,
                               std::string doctorID,
                               std::string doctorFirstName,
                               std::string doctorLastName,
                               std::string therapyName,
                               std::string therapyStatus);

struct ClientInfo {
    int clientId;
    std::string clientName;
    std::string clientType;
    ProbeMsg probeMsg;

    void SetClientInfo() {
        clientId = CLIENT_ID;
        clientName = CLIENT_NAME.front();
        clientType = CLIENT_TYPE.front();
        // probe msg
        probeMsg.set_medicaldeviceid(clientId);
        probeMsg.set_medicaldevicename(clientName);
        probeMsg.set_medicaldevicetype(clientType);
    }
};
