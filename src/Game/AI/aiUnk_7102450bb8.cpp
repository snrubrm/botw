#include "Game/AI/aiUnk_7102357210.h"

bool Unk_7102450bb8::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000a8)
        return false;

    _34 = *static_cast<const u32*>(message.getUserData());
    _30 = true;
    _18 = message.getSource();
    return true;
}
