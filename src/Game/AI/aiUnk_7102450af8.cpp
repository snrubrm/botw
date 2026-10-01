#include "Game/AI/aiUnk_7102357210.h"

bool Unk_7102450af8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x800003e)
        return false;

    _30 = true;
    _18 = message.getSource();
    return true;
}
