#include "ServerInfo.h"

ProbeMsgResponse PrepareProbeMatchData(int id, bool match, std::string& serverName) {
    ProbeMsgResponse probe;
    probe.set_medicalserverid(id);
    probe.set_medicalservername(serverName);
    probe.set_probematch(match);
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

void PrepareTherapyData(::TherapyData* thData,
                        std::string patientID,
                        std::string patientFirstName,
                        std::string patientLastName,
                        std::string doctorID,
                        std::string doctorFirstName,
                        std::string doctorLastName,
                        std::string therapyName,
                        std::string therapyStatus){

    thData->set_patientid(patientID);
    thData->set_patientfirstname(patientFirstName);
    thData->set_patientlastname(patientLastName);
    thData->set_doctorid(doctorID);
    thData->set_doctorfirstname(doctorFirstName);
    thData->set_doctorlastname(doctorLastName);
    thData->set_therapyname(therapyName);
    thData->set_therapystatus(therapyStatus);
    thData->set_currenttime(GetCurrentTime());
}

void PrepareTherapyList(::TherapyList* thList){
    TherapyData* thData = thList->add_therapies();
    PrepareTherapyData(thData, "P001", "John", "Johanson", "D001", "Mark", "Waston", "Medication A", "Started");
    TherapyData* thData2 = thList->add_therapies();
    PrepareTherapyData(thData2, "P002", "Tony", "Stark", "D012", "Alex", "Bolton", "Medication C", "Started");
}
