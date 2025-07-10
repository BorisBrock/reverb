#include "chat.h"

namespace chat {
void dummy() {}
}

extern "C" void chat_dummy() {
    chat::dummy();
}
