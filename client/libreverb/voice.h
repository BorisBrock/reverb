#pragma once

#include <vector>
#include <string>

namespace voice
{
    void dummy();
    std::vector<std::string> get_output_devices();
    std::vector<std::string> get_capture_devices();
}

#ifdef __cplusplus
extern "C"
{
#endif
    void voice_dummy();
    char **voice_get_output_devices(int *count);
    char **voice_get_capture_devices(int *count);
    void voice_free_device_list(char **list, int count);
    void voice_ws_connect(const char *uri);
    void voice_ws_disconnect();
#ifdef __cplusplus
}
#endif
