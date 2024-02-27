#include <iostream>
#include "Networking/HttpsClient.h"
#include "Domain/SoapMessageCreator.h"

// TODO: Prepare context for HTTPS communication
int main()
{
    std::string host{"127.0.0.1"};
    std::string port{"8080"};
    boost::asio::ssl::context ctx{boost::asio::ssl::context::tlsv13_client};
    auto client{std::make_shared<Networking::HttpsClient>(ctx ,false, host, port)};
    Domain::InitializeLibrary();
    auto message{Domain::PrepareSimpleSoapMessage()};
    Domain::DeinitializeLibrary();
    std::cout<<"Message: " << message << std::endl;
    client->SendRequest(message);
    return 0;
}
