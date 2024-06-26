#include <iostream>
#include <chrono>
#include "Networking/HttpsClient.h"
#include "Domain/SoapMessageCreator.h"
#include <thread>

// TODO: Prepare context for HTTPS communication
// TODO: Prepare function for measuring time

int main()
{
    // Get the current time before the code execution
    auto start = std::chrono::high_resolution_clock::now();

    Domain::InitializeLibrary();

    std::string host{"127.0.0.1"};
    std::string port{"8080"};
    boost::asio::ssl::context ctx{boost::asio::ssl::context::tlsv13_client};
    auto client{std::make_shared<Networking::HttpsClient>(ctx ,false, host, port)};

    auto message{Domain::PrepareProbeMessage()};
    client->SendRequest(message);
//    auto message2{Domain::PrepareTherapyMessage("P001",
//                                                "John",
//                                                "Johanson",
//                                                "D001",
//                                                "Mark",
//                                                "Waston",
//                                                "Medication A",
//                                                "Started")};
//    client->SendRequest(message2);

//    auto message3{Domain::PrepareTherapyListMessage()};
//    client->SendRequest(message3);


    Domain::DeinitializeLibrary();

    // Get the current time after the code execution
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the duration by subtracting start time from end time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // Output the duration
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
