#include <iostream>
#include "Networking/HttpsServer.h"
#include "Domain/SoapMessageCreator.h"

int main()
{
    Domain::InitializeLibrary();
    boost::asio::ssl::context context{boost::asio::ssl::context::tlsv13_client};
    auto listener = std::make_shared<Networking::HttpsListener>("127.0.0.1", 8080 ,context);
    listener->Run();
    listener->Run();
    listener->Run();
    Domain::DeinitializeLibrary();
    return 0;
}
