#include <memory>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>


namespace Networking {

class HttpsClient  : public std::enable_shared_from_this<HttpsClient> {

public:
    // Rule of five
    explicit HttpsClient(boost::asio::ssl::context& sslContext,
                         bool useHttps,
                         std::string host,
                         std::string port);
    ~HttpsClient();
    HttpsClient(const HttpsClient& other) = delete;
    HttpsClient(HttpsClient&& other) = delete;
    HttpsClient& operator=(const HttpsClient& other) = delete;
    HttpsClient& operator=(HttpsClient&& other) = delete;

    /**
     * @brief SendRequest
     * @param request
     */
    void SendRequest(std::string request);

private:
    /**
     * @brief Run
     */
    void Run();

    /**
     * @brief Resolve
     */
    void Resolve();

    /**
     * @brief OnResolve
     * @param ec
     * @param results
     */
    void OnResolve(boost::beast::error_code ec,
                   boost::asio::ip::tcp::resolver::results_type results);

    /**
     * @brief Connect
     * @param results
     */
    void Connect(const boost::asio::ip::tcp::resolver::results_type& results);

    /**
     * @brief OnConnect
     * @param ec
     * @param endpoint
     */
    void OnConnect(boost::beast::error_code ec,
                   boost::asio::ip::tcp::endpoint endpoint);

    /**
     * @brief Handshake
     */
    void Handshake();

    /**
     * @brief OnHandshake
     * @param ec
     */
    void OnHandshake(boost::beast::error_code ec);

    /**
     * @brief Write
     */
    void Write();

    /**
     * @brief OnWrite
     * @param ec
     * @param bytesTransferred
     */
    void OnWrite(boost::beast::error_code ec,
                 std::size_t bytesTransferred);

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
     * @brief CloseSocket
     */
    void CloseSocket();

    //TODO: Implement follwing method
    /**
     * @brief HandleResponse
     */
    void HandleResponse();

    boost::asio::io_context m_ioContext;
    boost::asio::ip::tcp::resolver m_resolver;
    boost::asio::ssl::context& m_sslContext;
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> m_stream;
    boost::beast::flat_buffer m_buffer;
    boost::beast::http::request<boost::beast::http::string_body> m_request;
    boost::beast::http::response<boost::beast::http::string_body> m_response;
    bool m_useHttps;
    std::string m_host;
    std::string m_port;
};

} // Networking
