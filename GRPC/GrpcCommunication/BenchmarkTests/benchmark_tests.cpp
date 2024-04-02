#include <iostream>
#include <benchmark/benchmark.h>
#include <../Client/ClientInfo.h>
#include <../Server/ServerInfo.h>
#include <chrono>

ProbeMsg PrepareProbeData(int id, std::string& clientName, std::string& clientType){
    ProbeMsg probe;
    probe.set_medicaldeviceid(id);
    probe.set_medicaldevicename(clientName);
    probe.set_medicaldevicetype(clientType);
    return probe;
}

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

static void BM_GrpcMessageCreationProbe(benchmark::State& state) {
    std::string clientName{"name"};
    std::string clientType{"type"};
    for (auto _ : state) {
        ProbeMsg probe = PrepareProbeData(0, clientName, clientType);
        std::string example{probe.SerializeAsString()};
    }
}
// Register the function as a benchmark
//BENCHMARK(BM_GrpcMessageCreationProbe);

static void BM_GrpcMessageCreationProbeMatch(benchmark::State& state) {
    std::string serverName{"name"};
    for (auto _ : state) {
        ProbeMsgResponse probe = PrepareProbeMatchData(0, true, serverName);
        std::string example{probe.SerializeAsString()};
    }
}
// Register the function as a benchmark
//BENCHMARK(BM_GrpcMessageCreationProbeMatch);


static void BM_GrpcMessageCreationTherapyData(benchmark::State& state){
    for (auto _ : state) {
        TherapyData thData = PrepareTherapyData("P001", "John", "Johanson", "D001", "Mark", "Waston", "Medication A", "Started");
        std::string example{thData.SerializeAsString()};
    }
}
BENCHMARK(BM_GrpcMessageCreationTherapyData);

static void BM_GrpcMessageCreationTherapyList(benchmark::State& state){
    for (auto _ : state) {
        TherapyList thList;
        TherapyData thData = PrepareTherapyData("P001", "John", "Johanson", "D001", "Mark", "Waston", "Medication A", "Started");
        *thList.add_therapies() = thData;
        TherapyData thData2 = PrepareTherapyData("P002", "Tony", "Stark", "D012", "Alex", "Bolton", "Medication C", "Started");
        *thList.add_therapies() = thData2;
        std::string example{thList.SerializeAsString()};
    }
}
BENCHMARK(BM_GrpcMessageCreationTherapyList);


static void BM_GrpcMessageParsingProbe(benchmark::State& state) {
    std::string clientName{"name"};
    std::string clientType{"type"};
    ProbeMsg probe = PrepareProbeData(0, clientName, clientType);
    std::string example{probe.SerializeAsString()};
    for (auto _ : state) {
        ProbeMsg newProbe;
        newProbe.ParseFromString(example);
        std::string parsedName{newProbe.medicaldevicename()};
        std::string parsedType{newProbe.medicaldevicetype()};
        int parsedId{newProbe.medicaldeviceid()};
    }
}
// Register the function as a benchmark
//BENCHMARK(BM_GrpcMessageParsingProbe);

static void BM_GrpcMessageParsingProbeMatch(benchmark::State& state) {
    std::string serverName{"name"};
    ProbeMsgResponse probe = PrepareProbeMatchData(0, true, serverName);
    std::string example{probe.SerializeAsString()};
    for (auto _ : state) {
        ProbeMsgResponse newProbe;
        newProbe.ParseFromString(example);
        std::string parsedName{newProbe.medicalservername()};
        int parsedid{newProbe.medicalserverid()};
        bool flag{newProbe.probematch()};
    }
}
// Register the function as a benchmark
//BENCHMARK(BM_GrpcMessageParsingProbeMatch);

static void BM_GrpcMessageParsingTherapyData(benchmark::State& state){
    TherapyData thData = PrepareTherapyData("P001", "John", "Johanson", "D001", "Mark", "Waston", "Medication A", "Started");
    std::string example{thData.SerializeAsString()};
    for (auto _ : state) {
        TherapyData newThData;
        newThData.ParseFromString(example);
        std::string patientID{newThData.patientid()};
        std::string patientFirstName{newThData.patientfirstname()};
        std::string patientLastName{newThData.patientlastname()};
        std::string doctorID{newThData.doctorid()};
        std::string doctorFirstName{newThData.doctorfirstname()};
        std::string doctorLastName{newThData.doctorlastname()};
        std::string therapyName{newThData.therapyname()};
        std::string therapyStatus{newThData.therapystatus()};
        std::string currentTime{newThData.currenttime()};
    }
}
BENCHMARK(BM_GrpcMessageParsingTherapyData);

static void BM_GrpcMessageParsingTherapyList(benchmark::State& state){
    TherapyList thList;
    TherapyData thData = PrepareTherapyData("P001", "John", "Johanson", "D001", "Mark", "Waston", "Medication A", "Started");
    *thList.add_therapies() = thData;
    TherapyData thData2 = PrepareTherapyData("P002", "Tony", "Stark", "D012", "Alex", "Bolton", "Medication C", "Started");
    *thList.add_therapies() = thData2;
    std::string example{thList.SerializeAsString()};
    for (auto _ : state) {
        TherapyList newThList;
        newThList.ParseFromString(example);
        for(const TherapyData& thData : newThList.therapies()){
            std::string patientID{thData.patientid()};
            std::string patientFirstName{thData.patientfirstname()};
            std::string patientLastName{thData.patientlastname()};
            std::string doctorID{thData.doctorid()};
            std::string doctorFirstName{thData.doctorfirstname()};
            std::string doctorLastName{thData.doctorlastname()};
            std::string therapyName{thData.therapyname()};
            std::string therapyStatus{thData.therapystatus()};
            std::string currentTime{thData.currenttime()};
        }
    }
}
BENCHMARK(BM_GrpcMessageParsingTherapyList);

BENCHMARK_MAIN();
