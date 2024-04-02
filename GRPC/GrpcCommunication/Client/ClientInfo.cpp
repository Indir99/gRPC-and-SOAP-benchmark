#include "ClientInfo.h"

ProbeMsg PrepareProbeData(int id, std::string& clientName, std::string& clientType){
    ProbeMsg probe;
    probe.set_medicaldeviceid(id);
    probe.set_medicaldevicename(clientName);
    probe.set_medicaldevicetype(clientType);
    return probe;
}

std::string GetCurrentTime(){
    // Get current time
    auto currentTime = std::chrono::system_clock::now();
    // Convert the time point to a time_t (seconds since epoch)
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
    // Format the time as a string
    char timeBuffer[80];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTimeT));
    // Store the formatted time in a std::string
    std::string formattedTime(timeBuffer);
    return formattedTime;
}

TherapyData PrepareTherapyData(std::string patientID,
                               std::string patientFirstName,
                               std::string patientLastName,
                               std::string doctorID,
                               std::string doctorFirstName,
                               std::string doctorLastName,
                               std::string therapyName,
                               std::string therapyStatus){
    TherapyData thData;
    thData.set_patientid(patientID);
    thData.set_patientfirstname(patientFirstName);
    thData.set_patientlastname(patientLastName);
    thData.set_doctorid(doctorID);
    thData.set_doctorfirstname(doctorFirstName);
    thData.set_doctorlastname(doctorLastName);
    thData.set_therapyname(therapyName);
    thData.set_therapystatus(therapyStatus);
    thData.set_currenttime(GetCurrentTime());
    return thData;
}
