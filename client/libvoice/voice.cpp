#include "voice.h"

namespace voice {
void dummy() {}
}

extern "C" void voice_dummy() {
    voice::dummy();
}
