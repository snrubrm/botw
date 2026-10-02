#include "Game/AI/aiUnk_7102357210.h"

bool Unk_7102450828::m2(const ksys::Message& message) {
    if (Unk_7102450648::m2(message))
        return true;

    if (message.getType() == 0x8000009) {
        _8 = *static_cast<const ksys::act::BaseProcLink*>(message.getUserData());
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    return false;
}
