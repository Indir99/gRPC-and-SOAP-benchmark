#pragma once

#include <memory>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/asio/ssl.hpp>


namespace Networking {

class HttpsSession : public std::enable_shared_from_this<HttpsSession> {

public:
    explicit HttpsSession(boost::asio::ip::tcp::socket&& socket,
                          boost::asio::ssl::context& sslContext);
    ~HttpsSession();
    HttpsSession(const HttpsSession& other) = delete;
    HttpsSession(HttpsSession&& other) = delete;
    HttpsSession& operator=(const HttpsSession& other) = delete;
    HttpsSession& operator=(HttpsSession&& other) = delete;

    /**
     * @brief Run
     */
    void Run();

private:

    /**
     * @brief Read
     */
    void Read();

    /**
     * @brief OnRead
     * @param ec
     * @param bytesTransferred
     */
    void OnRead(boost::beast::error_code ec,
                std::size_t bytesTransferred);

    /**
     * @brief HandleRequest
     * @return
     */
    boost::beast::http::response<boost::beast::http::string_body> HandleRequest();

    /**
     * @brief Write
     */
    void Write();

    /**
     * @brief OnWrite
     * @param ec
     * @param bytes_transferred
     */
    void OnWrite(boost::beast::error_code ec,
                 std::size_t bytes_transferred);

    void CloseSocket();

    boost::beast::flat_buffer m_buffer;
    boost::beast::http::request<boost::beast::http::string_body> m_request;
    boost::beast::http::response<boost::beast::http::string_body> m_response;
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> m_stream;
    boost::asio::ssl::context& m_sslContext;


};

class HttpsListener : public std::enable_shared_from_this<HttpsListener> {

public:
    explicit HttpsListener(std::string address, unsigned short port, boost::asio::ssl::context& sslContext);
    ~HttpsListener();
    HttpsListener(const HttpsListener& other) = delete;
    HttpsListener(HttpsListener&& other) = delete;
    HttpsListener& operator=(const HttpsListener& other) = delete;
    HttpsListener& operator=(HttpsListener&& other) = delete;

    void Run();

private:
    void PrepareAcceptor();
    void Accept();
    void OnAccept(boost::beast::error_code ec,
                  boost::asio::ip::tcp::socket stream);

    boost::asio::io_context m_ioContext;
    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::asio::ssl::context& m_sslContext;
    std::string m_address;
    unsigned short m_port;
};


class HttpsServer : public std::enable_shared_from_this<HttpsServer> {
    //TODO: Implement server class that will manipulate with Listener and Sessions
};

} // Networking
