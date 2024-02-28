#include <iostream>
#include <chrono>
#include "Networking/HttpsClient.h"
#include "Domain/SoapMessageCreator.h"

// TODO: Prepare context for HTTPS communication
// TODO: Prepare function for measuring time

int main()
{
    Domain::InitializeLibrary();

    // Get the current time before the code execution
    auto start = std::chrono::high_resolution_clock::now();
    std::string host{"127.0.0.1"};
    std::string port{"8080"};
    boost::asio::ssl::context ctx{boost::asio::ssl::context::tlsv13_client};
    auto client{std::make_shared<Networking::HttpsClient>(ctx ,false, host, port)};

    auto message{Domain::PrepareProbeMessage()};
    client->SendRequest(message);

    // Get the current time after the code execution
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the duration by subtracting start time from end time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // Output the duration
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    Domain::DeinitializeLibrary();

    return 0;
}
