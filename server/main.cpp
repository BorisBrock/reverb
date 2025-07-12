#include <iostream>
#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>
#include <nng/protocol/pipeline0/pull.h>

constexpr const char* PULL_ADDR = "tcp://127.0.0.1:6001";
constexpr const char* PUB_ADDR  = "tcp://127.0.0.1:6002";

int main()
{
    nng_socket pullSock;
    nng_socket pubSock;
    int rv;

    if ((rv = nng_pull0_open(&pullSock)) != 0) {
        std::cerr << "failed to open pull socket: " << nng_strerror(rv) << std::endl;
        return 1;
    }

    if ((rv = nng_pub0_open(&pubSock)) != 0) {
        std::cerr << "failed to open pub socket: " << nng_strerror(rv) << std::endl;
        return 1;
    }

    if ((rv = nng_listen(pullSock, PULL_ADDR, nullptr, 0)) != 0) {
        std::cerr << "failed to listen on " << PULL_ADDR << ": " << nng_strerror(rv) << std::endl;
        return 1;
    }

    if ((rv = nng_listen(pubSock, PUB_ADDR, nullptr, 0)) != 0) {
        std::cerr << "failed to listen on " << PUB_ADDR << ": " << nng_strerror(rv) << std::endl;
        return 1;
    }

    std::cout << "reverb server running" << std::endl;

    while (true) {
        char* msg = nullptr;
        size_t size = 0;
        if ((rv = nng_recv(pullSock, &msg, &size, NNG_FLAG_ALLOC)) == 0) {
            nng_send(pubSock, msg, size, 0);
            std::cout << "chat: " << msg << std::endl;
            nng_free(msg, size);
        } else {
            std::cerr << "recv error: " << nng_strerror(rv) << std::endl;
        }
    }

    nng_close(pullSock);
    nng_close(pubSock);
    return 0;
}
