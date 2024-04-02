#include <iostream>
#include <benchmark/benchmark.h>
#include <../Domain/SoapMessageCreator.h>
#include <../Domain/XmlParser.h>

static void BM_SoapMessageCreationProbe(benchmark::State& state) {
    Domain::InitializeLibrary();
    for (auto _ : state) {
        auto message{Domain::PrepareProbeMessage()};
    }
    Domain::DeinitializeLibrary();
}
// Register the function as a benchmark
BENCHMARK(BM_SoapMessageCreationProbe);

static void BM_SoapMessageCreationProbeMatch(benchmark::State& state) {
    Domain::InitializeLibrary();
    for (auto _ : state) {
        auto message{Domain::PrepareProbeMatchMessage()};
    }
    Domain::DeinitializeLibrary();
}
// Register the function as a benchmark
BENCHMARK(BM_SoapMessageCreationProbeMatch);

static void BM_SoapMessageCreationTherapyData(benchmark::State& state) {
    Domain::InitializeLibrary();
    for (auto _ : state) {
        auto message{Domain::PrepareTherapyMessage("P001", "John", "Johanson",
                                                   "D001", "Mark", "Waston",
                                                   "Medication A", "Started")};
    }
    Domain::DeinitializeLibrary();
}
BENCHMARK(BM_SoapMessageCreationTherapyData);

static void BM_SoapMessageCreationTherapyList(benchmark::State& state) {
    Domain::InitializeLibrary();
    for (auto _ : state) {
        auto message{Domain::PrepareTherapyListMessage()};
    }
    Domain::DeinitializeLibrary();
}
// Register the function as a benchmark
BENCHMARK(BM_SoapMessageCreationTherapyList);


static void BM_SoapMessageParsingProbe(benchmark::State& state) {
    Domain::InitializeLibrary();
    auto message{Domain::PrepareProbeMessage()};
    for (auto _ : state) {
        Domain::XmlParser parser{};
        parser.ParseMessage(message);
        Domain::ProbeData probe;
        parser.GetProbeData(probe);
    }
    Domain::DeinitializeLibrary();
}
// Register the function as a benchmark
//BENCHMARK(BM_SoapMessageParsingProbe);

static void BM_SoapMessageParsingProbeMatch(benchmark::State& state) {
    Domain::InitializeLibrary();
    auto message{Domain::PrepareProbeMatchMessage()};
    for (auto _ : state) {
        Domain::XmlParser parser{};
        parser.ParseMessage(message);
        Domain::ProbeMatchData probe;
        parser.GetProbeMatchData(probe);
    }
    Domain::DeinitializeLibrary();
}
// Register the function as a benchmark
//BENCHMARK(BM_SoapMessageParsingProbeMatch);

static void BM_SoapMessageParsingTherapyData(benchmark::State& state) {
    Domain::InitializeLibrary();
    auto message{Domain::PrepareTherapyMessage("P001", "John", "Johanson",
                                               "D001", "Mark", "Waston",
                                               "Medication A", "Started")};
    for (auto _ : state) {
        Domain::XmlParser parser{};
        parser.ParseMessage(message);
        Domain::TherapyData thData;
        parser.GetTherapyData(thData);
    }
    Domain::DeinitializeLibrary();
}
// Register the function as a benchmark
//BENCHMARK(BM_SoapMessageParsingTherapyData);

static void BM_SoapMessageParsingTherapyList(benchmark::State& state) {
    Domain::InitializeLibrary();
    auto message{Domain::PrepareTherapyListMessage()};
    for (auto _ : state) {
        Domain::XmlParser parser{};
        parser.ParseMessage(message);
        Domain::TherapyList thList;
        parser.GetTherapyListData(thList);
    }
    Domain::DeinitializeLibrary();
}
// Register the function as a benchmark
//BENCHMARK(BM_SoapMessageParsingTherapyList);


BENCHMARK_MAIN();
