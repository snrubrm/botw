#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_71005D6D10.h"

// NON_MATCHING: regalloc (&_8 is materialised before the getUserData call)
bool Unk_71024507c8::m2(const ksys::Message& message) {
    if (Unk_7102450648::m2(message))
        return true;

    if (message.getType() == 0x8000001) {
        _8.acquire(static_cast<ksys::act::BaseProc*>(message.getUserData()), false);
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    return false;
}

void Unk_71024507c8::sub_710070B5A0(ksys::act::Actor* actor) {
    sub_71007094F4(actor);
    sub_71005DC5DC(actor);
}
