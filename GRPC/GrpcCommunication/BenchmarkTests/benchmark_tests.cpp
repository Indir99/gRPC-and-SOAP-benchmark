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
        std::string example{probe.SerializeAsString()};
    }
}
// Register the function as a benchmark
BENCHMARK(BM_GrpcMessageCreationProbe);

static void BM_GrpcMessageCreationProbeMatch(benchmark::State& state) {
    std::string serverName{"name"};
    for (auto _ : state) {
        ProbeMsgResponse probe = PrepareProbeMatchData(0, true, serverName);
        std::string example{probe.SerializeAsString()};
    }
}
// Register the function as a benchmark
BENCHMARK(BM_GrpcMessageCreationProbeMatch);

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
BENCHMARK(BM_GrpcMessageParsingProbe);

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
BENCHMARK(BM_GrpcMessageParsingProbeMatch);

BENCHMARK_MAIN();
