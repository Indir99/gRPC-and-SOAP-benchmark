#include "Client.h"
#include <iostream>


int main(int argc, char* argv[])
{
    // Get the current time before the code execution
    auto start = std::chrono::high_resolution_clock::now();

    ClientInfo clientInformations;
    clientInformations.SetClientInfo();
    GrpcClient client{"localhost:50051", clientInformations};
    client.SendProbe();

    // Get the current time after the code execution
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the duration by subtracting start time from end time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // Output the duration
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
