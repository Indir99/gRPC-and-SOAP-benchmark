#include <iostream>
#include "Networking/HttpsServer.h"

int main()
{
    boost::asio::ssl::context context{boost::asio::ssl::context::tlsv13_client};
    auto listener = std::make_shared<Networking::HttpsListener>("127.0.0.1", 8080 ,context);
    listener->Run();
    return 0;
}
