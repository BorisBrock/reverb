#include "voice.h"
#include "miniaudio.h"
#include <cstdlib>
#include <cstring>

namespace voice {

void dummy() {}

static std::vector<std::string> list_devices(ma_device_type type)
{
    ma_context context;
    if (ma_context_init(NULL, 0, NULL, &context) != MA_SUCCESS) {
        return {};
    }

    ma_device_info* playbackInfos = NULL;
    ma_uint32 playbackCount = 0;
    ma_device_info* captureInfos = NULL;
    ma_uint32 captureCount = 0;

    if (ma_context_get_devices(&context, &playbackInfos, &playbackCount,
                               &captureInfos, &captureCount) != MA_SUCCESS) {
        ma_context_uninit(&context);
        return {};
    }

    std::vector<std::string> result;
    ma_device_info* infos =
        (type == ma_device_type_playback) ? playbackInfos : captureInfos;
    ma_uint32 count =
        (type == ma_device_type_playback) ? playbackCount : captureCount;

    for (ma_uint32 i = 0; i < count; ++i) {
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

} // namespace voice

extern "C" {

void voice_dummy()
{
    voice::dummy();
}

static char** to_c_array(const std::vector<std::string>& vec, int* count)
{
    if (count)
        *count = static_cast<int>(vec.size());

    if (vec.empty())
        return nullptr;

    char** list =
        static_cast<char**>(std::malloc(vec.size() * sizeof(char*)));
    for (size_t i = 0; i < vec.size(); ++i) {
        list[i] = static_cast<char*>(std::malloc(vec[i].size() + 1));
        std::memcpy(list[i], vec[i].c_str(), vec[i].size() + 1);
    }
    return list;
}

char** voice_get_output_devices(int* count)
{
    auto devices = voice::get_output_devices();
    return to_c_array(devices, count);
}

char** voice_get_capture_devices(int* count)
{
    auto devices = voice::get_capture_devices();
    return to_c_array(devices, count);
}

void voice_free_device_list(char** list, int count)
{
    if (!list)
        return;
    for (int i = 0; i < count; ++i) {
        std::free(list[i]);
    }
    std::free(list);
}

} // extern "C"
