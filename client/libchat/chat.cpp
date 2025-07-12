#include "chat.h"

#include <nng/nng.h>
#include <nng/protocol/pubsub0/sub.h>
#include <nng/protocol/pipeline0/push.h>

#include <atomic>
#include <cstring>
#include <thread>

namespace chat
{

    constexpr const char *PUSH_ADDR = "tcp://127.0.0.1:6001";
    constexpr const char *SUB_ADDR = "tcp://127.0.0.1:6002";

    static nng_socket pushSock;
    static nng_socket subSock;
    static std::thread recvThread;
    static std::atomic<bool> running{false};
    static message_callback callback = nullptr;

    static void recv_loop()
    {
        while (running)
        {
            char *msg = nullptr;
            size_t size = 0;
            int rv = nng_recv(subSock, &msg, &size, NNG_FLAG_ALLOC);
            if (rv == 0)
            {
                if (callback)
                    callback(msg);
                nng_free(msg, size);
            }
            else if (rv == NNG_ETIMEDOUT)
            {
                continue;
            }
        }
    }

    bool start(message_callback cb)
    {
        callback = cb;
        int rv;
        if ((rv = nng_push0_open(&pushSock)) != 0)
            return false;
        if ((rv = nng_sub0_open(&subSock)) != 0)
            return false;
        if ((rv = nng_setopt(subSock, NNG_OPT_SUB_SUBSCRIBE, "", 0)) != 0)
            return false;
        if ((rv = nng_dial(pushSock, PUSH_ADDR, nullptr, 0)) != 0)
            return false;
        if ((rv = nng_dial(subSock, SUB_ADDR, nullptr, 0)) != 0)
            return false;

        running = true;
        recvThread = std::thread(recv_loop);
        return true;
    }

    void publish(const char *message)
    {
        if (!message)
            return;
        nng_send(pushSock, (void *)message, std::strlen(message) + 1, 0);
    }

    void stop()
    {
        running = false;
        nng_close(pushSock);
        nng_close(subSock);
        if (recvThread.joinable())
            recvThread.join();
    }

} // namespace chat

extern "C"
{

    bool chat_start(chat_message_callback cb)
    {
        return chat::start(cb);
    }

    void chat_publish(const char *message)
    {
        chat::publish(message);
    }

    void chat_stop()
    {
        chat::stop();
    }
}
