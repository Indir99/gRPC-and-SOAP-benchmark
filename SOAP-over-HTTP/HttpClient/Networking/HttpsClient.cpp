#include "HttpsClient.h"
#include <iostream>

namespace Networking {

namespace {

namespace beast = boost::beast;
namespace http = beast::http;

http::request<http::string_body> PrepareHttpPostMessage(std::string message, std::string host) {
    http::request<http::string_body> req{http::verb::post, "/post", 11};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, "Boost");
    req.set(http::field::content_type, "text/plain");
    req.body() = message;
    req.prepare_payload();
    return req;
}

} // namespace

HttpsClient::HttpsClient(boost::asio::ssl::context& sslContext,
                         bool useHttps,
                         std::string host,
                         std::string port) :
    m_ioContext{},
    m_resolver{m_ioContext},
    m_sslContext{sslContext},
    m_stream{m_ioContext, m_sslContext},
    m_useHttps{useHttps},
    m_host{host},
    m_port{port}
{
}

HttpsClient::~HttpsClient(){
    m_ioContext.stop();
}

void HttpsClient::Run() {
    // Start the asynchronous operation
    Resolve();
    m_ioContext.run();
}

void HttpsClient::Resolve() {
    // Look up the domain name
    m_resolver.async_resolve(
        m_host,
        m_port,
        boost::beast::bind_front_handler(
            &HttpsClient::OnResolve,
            shared_from_this()));
}

void HttpsClient::OnResolve(boost::beast::error_code ec,
                            boost::asio::ip::tcp::resolver::results_type results){
    if(ec){
        // Add error Handling
    }
    Connect(results);
}

void HttpsClient::Connect(const boost::asio::ip::tcp::resolver::results_type& results){

    boost::asio::async_connect(m_stream.next_layer(),
                               results,
                               boost::beast::bind_front_handler(
                                   &HttpsClient::OnConnect,
                                   shared_from_this()));
}

void HttpsClient::OnConnect(boost::beast::error_code ec,
                            boost::asio::ip::tcp::endpoint endpoint){
    if(ec){
        // Add Error Handling
    }
    if(not m_useHttps) {
        Write();
    } else {
        Handshake();
    }
}

void HttpsClient::Handshake(){
    m_stream.async_handshake(boost::asio::ssl::stream_base::client,
                             boost::beast::bind_front_handler(
                                 &HttpsClient::OnHandshake,
                                 shared_from_this()));
}

void HttpsClient::OnHandshake(boost::beast::error_code ec){
    if(ec){
        //Add error handling
    }
    Write();
}

void HttpsClient::Write() {
    // Simple solution:
    // for http communication: use tpc socket or m_stream.next_layer()
    // for https Communction: use ssl socket or m_stream
    if(not m_useHttps) {
        boost::beast::http::async_write(m_stream.next_layer(),
                                        m_request,
                                        boost::beast::bind_front_handler(
                                            &HttpsClient::OnWrite,
                                            shared_from_this()));
    } else {
        boost::beast::http::async_write(m_stream,
                                        m_request,
                                        boost::beast::bind_front_handler(
                                            &HttpsClient::OnWrite,
                                            shared_from_this()));
    }
}

void HttpsClient::OnWrite(boost::beast::error_code ec,
                          std::size_t bytesTransferred) {

    boost::ignore_unused(bytesTransferred);
    if(ec) {
        // Add error Handling
    }
    if(0 == bytesTransferred) {
        // Add error Handling
    }
    Read();
}

void HttpsClient::Read() {
    // Simple solution:
    // for http communication: use tpc socket or m_stream.next_layer()
    // for https Communction: use ssl socket or m_stream
    if(not m_useHttps) {
        boost::beast::http::async_read(m_stream.next_layer(),
                                       m_buffer,
                                       m_response,
                                       boost::beast::bind_front_handler(
                                           &HttpsClient::OnRead,
                                           shared_from_this()));
    } else {
        boost::beast::http::async_read(m_stream,
                                       m_buffer,
                                       m_response,
                                       boost::beast::bind_front_handler(
                                           &HttpsClient::OnRead,
                                           shared_from_this()));
    }
}

void HttpsClient::OnRead(boost::beast::error_code ec,
                         std::size_t bytesTransferred) {

    boost::ignore_unused(bytesTransferred);
    if(ec) {
        // Add error Handling
    }
    if(0 == bytesTransferred) {
        // Add error Handling
    }
    CloseSocket();
    // Do whatever you want with message
    std::cout<<m_response.body()<<std::endl;
}

void HttpsClient::CloseSocket(){
    boost::beast::error_code ec;
    m_stream.next_layer().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    if(ec && ec != boost::beast::errc::not_connected) {
        // Handle following case
    }
}

void HttpsClient::SendRequest(std::string request){
    m_request = PrepareHttpPostMessage(request, m_host);
    Run();
}

} // Networking
