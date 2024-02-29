#include <iostream>
#include <benchmark/benchmark.h>
#include <../Client/ClientInfo.h>
#include <../Server/ServerInfo.h>

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

static void BM_GrpcMessageCreationProbe(benchmark::State& state) {
    std::string clientName{"name"};
    std::string clientType{"type"};
    for (auto _ : state) {
        ProbeMsg probe = PrepareProbeData(0, clientName, clientType);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_GrpcMessageCreationProbe);

static void BM_GrpcMessageCreationProbeMatch(benchmark::State& state) {
    std::string serverName{"name"};
    for (auto _ : state) {
        ProbeMsgResponse probe = PrepareProbeMatchData(0, true, serverName);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_GrpcMessageCreationProbeMatch);

static void BM_GrpcMessageParsingProbe(benchmark::State& state) {
    std::string clientName{"name"};
    std::string clientType{"type"};
    ProbeMsg probe = PrepareProbeData(0, clientName, clientType);
    for (auto _ : state) {
        std::string parsedName{probe.medicaldevicename()};
        std::string parsedType{probe.medicaldevicetype()};
        int parsedId{probe.medicaldeviceid()};
    }
}
// Register the function as a benchmark
BENCHMARK(BM_GrpcMessageParsingProbe);

static void BM_GrpcMessageParsingProbeMatch(benchmark::State& state) {
    std::string serverName{"name"};
    ProbeMsgResponse probe = PrepareProbeMatchData(0, true, serverName);
    for (auto _ : state) {
        std::string parsedName{probe.medicalservername()};
        int parsedid{probe.medicalserverid()};
        bool flag{probe.probematch()};
    }
}
// Register the function as a benchmark
BENCHMARK(BM_GrpcMessageParsingProbeMatch);

//static void BM_SoapMessageParsingProbeMatch(benchmark::State& state) {
//    Domain::InitializeLibrary();
//    auto message{Domain::PrepareProbeMatchMessage()};
//    for (auto _ : state) {
//        Domain::XmlParser parser{};
//        parser.ParseMessage(message);
//        Domain::ProbeMatchData probe;
//        parser.GetProbeMatchData(probe);
//    }
//    Domain::DeinitializeLibrary();
//}
//// Register the function as a benchmark
//BENCHMARK(BM_SoapMessageParsingProbeMatch);

BENCHMARK_MAIN();
