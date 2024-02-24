#include <iostream>
#include "Networking/HttpsClient.h"


// TODO: Prepare context for HTTPS communication
int main()
{
    std::string host{"127.0.0.1"};
    std::string port{"8080"};
    boost::asio::ssl::context ctx{boost::asio::ssl::context::tlsv13_client};
    auto client{std::make_shared<Networking::HttpsClient>(ctx ,false, host, port)};
    std::string dummyRequest{"DummyText"};
    client->SendRequest(dummyRequest);
    return 0;
}
