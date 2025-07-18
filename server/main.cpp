#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <iostream>
#include <cstdlib>

using websocketpp::connection_hdl;
typedef websocketpp::server<websocketpp::config::asio> server;

class ReverbServer {
public:
    ReverbServer() {
        m_server.init_asio();
        m_server.set_open_handler([](connection_hdl){
            std::cout << "Client connected" << std::endl;
        });
        m_server.set_close_handler([](connection_hdl){
            std::cout << "Client disconnected" << std::endl;
        });
        m_server.set_message_handler([](connection_hdl, server::message_ptr msg){
            std::cout << "Message: " << msg->get_payload() << std::endl;
        });
    }

    void run(uint16_t port) {
        m_server.listen(port);
        m_server.start_accept();
        m_server.run();
    }

private:
    server m_server;
};

int main(int argc, char* argv[])
{
    uint16_t port = 8080;
    if (argc > 1)
        port = static_cast<uint16_t>(std::atoi(argv[1]));

    try {
        ReverbServer srv;
        srv.run(port);
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
