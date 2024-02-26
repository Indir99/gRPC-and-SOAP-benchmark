#include "HttpsServer.h"
#include <iostream>

namespace Networking {

HttpsSession::HttpsSession(boost::asio::ip::tcp::socket&& socket,
                           boost::asio::ssl::context& sslContext)
    : m_sslContext{sslContext}
    , m_stream{std::move(socket), sslContext}
{}

HttpsSession::~HttpsSession(){}

void HttpsSession::Run(){
    // We need to be executing within a strand to perform async operations
    // on the I/O objects in this session. Although not strictly necessary
    // for single-threaded contexts, this example code is written to be
    // thread-safe by default.
    boost::asio::dispatch(m_stream.get_executor(),
                          boost::beast::bind_front_handler(&HttpsSession::Read,
                                                           shared_from_this()));
}

void HttpsSession::Read(){
    m_request = {};
    boost::beast::http::async_read(m_stream.next_layer(),
                                   m_buffer,
                                   m_request,
                                   boost::beast::bind_front_handler(&HttpsSession::OnRead,
                                                                    shared_from_this()));
}

void HttpsSession::OnRead(boost::beast::error_code ec,
                          std::size_t bytesTransferred) {
    boost::ignore_unused(bytesTransferred);
    if(ec) {
        //Error handling
    }
    std::cout<<"Received meesage: "<<m_request.body() << std::endl;
}



HttpsListener::HttpsListener(std::string address, unsigned short port, boost::asio::ssl::context& sslContext)
    : m_ioContext{}
    , m_acceptor{m_ioContext}
    , m_sslContext{sslContext}
    , m_address{address}
    , m_port{port} {
}

HttpsListener::~HttpsListener(){}

void HttpsListener::Run(){
    PrepareAcceptor();
    Accept();
}

void HttpsListener::PrepareAcceptor(){
    boost::beast::error_code ec;
    boost::asio::ip::tcp::endpoint endpoint{boost::asio::ip::make_address(m_address), m_port};

    m_acceptor.open(endpoint.protocol(), ec);
    if(ec) {
        //Error handling
    }

    // Allow address reuse
    m_acceptor.set_option(boost::asio::socket_base::reuse_address(true), ec);
    if(ec) {
        //Error handling
    }

    // Bind to the server address
    m_acceptor.bind(endpoint, ec);
    if(ec)
    {
        //Error handling
    }

    // Start listening for connections
    m_acceptor.listen(boost::asio::socket_base::max_listen_connections, ec);
    if(ec) {
        // Error handling
        return;
    }
}

void HttpsListener::Accept(){
    m_acceptor.async_accept(m_ioContext,
                            boost::beast::bind_front_handler(&HttpsListener::OnAccept,
                                                             shared_from_this()));
    m_ioContext.run();
}

void HttpsListener::OnAccept(boost::beast::error_code ec,
                             boost::asio::ip::tcp::socket stream){
    if(ec){
        //Error Handling
    } else {
        //Prepare Session
        auto session{std::make_shared<HttpsSession>(std::move(stream), m_sslContext)};
        session->Run();
    }
}

} // Networking
