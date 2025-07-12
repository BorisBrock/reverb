#pragma once

#include <stddef.h>

namespace chat {
using message_callback = void(*)(const char*);

bool start(message_callback cb);
void publish(const char* message);
void stop();
}

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*chat_message_callback)(const char*);

bool chat_start(chat_message_callback cb);
void chat_publish(const char* message);
void chat_stop();

#ifdef __cplusplus
}
#endif
