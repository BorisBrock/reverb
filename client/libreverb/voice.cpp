#include "miniaudio.c"
#include "voice.h"
#include <cstdlib>
#include <cstring>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <thread>
#include <memory>

namespace voice
{
    static std::vector<std::string> list_devices(ma_device_type type)
    {
        ma_context context;
        if (ma_context_init(NULL, 0, NULL, &context) != MA_SUCCESS)
        {
            return {};
        }

        ma_device_info *playbackInfos = NULL;
        ma_uint32 playbackCount = 0;
        ma_device_info *captureInfos = NULL;
        ma_uint32 captureCount = 0;

        if (ma_context_get_devices(&context, &playbackInfos, &playbackCount,
                                   &captureInfos, &captureCount) != MA_SUCCESS)
        {
            ma_context_uninit(&context);
            return {};
        }

        std::vector<std::string> result;
        ma_device_info *infos =
            (type == ma_device_type_playback) ? playbackInfos : captureInfos;
        ma_uint32 count =
            (type == ma_device_type_playback) ? playbackCount : captureCount;

        for (ma_uint32 i = 0; i < count; ++i)
        {
            result.emplace_back(infos[i].name);
        }

        ma_context_uninit(&context);
        return result;
    }

    std::vector<std::string> get_output_devices()
    {
        return list_devices(ma_device_type_playback);
    }

    std::vector<std::string> get_capture_devices()
    {
        return list_devices(ma_device_type_capture);
    }

    using ws_client = websocketpp::client<websocketpp::config::asio_client>;

    static std::unique_ptr<ws_client> g_client;
    static websocketpp::connection_hdl g_hdl;
    static std::thread g_thread;

    static void run_client()
    {
        if (g_client)
            g_client->run();
    }

    void ws_connect(const std::string &uri)
    {
        if (g_client)
            return;

        g_client.reset(new ws_client());
        g_client->init_asio();
        g_client->set_open_handler([](websocketpp::connection_hdl)
                                   { std::cout << "WS connected" << std::endl; });
        g_client->set_close_handler([](websocketpp::connection_hdl)
                                    { std::cout << "WS closed" << std::endl; });
        g_client->set_fail_handler([](websocketpp::connection_hdl)
                                   { std::cout << "WS failed" << std::endl; });

        websocketpp::lib::error_code ec;
        ws_client::connection_ptr con = g_client->get_connection(uri, ec);
        if (ec)
        {
            std::cout << "get_connection error: " << ec.message() << std::endl;
            g_client.reset();
            return;
        }
        g_hdl = con->get_handle();
        g_client->connect(con);
        g_thread = std::thread(run_client);
    }

    void ws_disconnect()
    {
        if (!g_client)
            return;

        websocketpp::lib::error_code ec;
        g_client->close(g_hdl, websocketpp::close::status::normal, "", ec);
        if (ec)
        {
            std::cout << "close error: " << ec.message() << std::endl;
        }
        g_client->stop();
        if (g_thread.joinable())
            g_thread.join();
        g_client.reset();
    }
} // namespace voice

extern "C"
{
    static char **to_c_array(const std::vector<std::string> &vec, int *count)
    {
        if (count)
            *count = static_cast<int>(vec.size());

        if (vec.empty())
            return nullptr;

        char **list =
            static_cast<char **>(std::malloc(vec.size() * sizeof(char *)));
        for (size_t i = 0; i < vec.size(); ++i)
        {
            list[i] = static_cast<char *>(std::malloc(vec[i].size() + 1));
            std::memcpy(list[i], vec[i].c_str(), vec[i].size() + 1);
        }
        return list;
    }

    char **voice_get_output_devices(int *count)
    {
        auto devices = voice::get_output_devices();
        return to_c_array(devices, count);
    }

    char **voice_get_capture_devices(int *count)
    {
        auto devices = voice::get_capture_devices();
        return to_c_array(devices, count);
    }

    void voice_free_device_list(char **list, int count)
    {
        if (!list)
            return;
        for (int i = 0; i < count; ++i)
        {
            std::free(list[i]);
        }
        std::free(list);
    }

    void voice_ws_connect(const char *uri)
    {
        if (uri)
            voice::ws_connect(uri);
    }

    void voice_ws_disconnect()
    {
        voice::ws_disconnect();
    }

} // extern "C"
