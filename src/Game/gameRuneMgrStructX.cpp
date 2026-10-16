#include "Game/gameRuneMgrStructX.h"

namespace uking {

void Unk_710067e0a8::sub_710067ED08(ksys::act::BaseProc* bomb, s32 bit, bool on) {
    const u8 mask = 1 << bit;
    for (auto& slot : mSlots) {
        if (slot.bomb.hasProcById(bomb)) {
            if (on)
                slot.flags.set(mask);
            else
                slot.flags.reset(mask);
        }
    }
}

void Unk_710067e0a8::sub_710067EDDC(ksys::act::BaseProc* bomb, const ksys::act::BaseProcLink& target) {
    for (auto& slot : mSlots) {
        if (slot.bomb.hasProcById(bomb)) {
            slot.target = target;
            slot.flags.set(0x10);
        }
    }
}

void Unk_710067e0a8::sub_710067EE7C(ksys::act::BaseProc* bomb) {
    for (auto& slot : mSlots) {
        if (slot.bomb.hasProcById(bomb)) {
            slot.target.reset();
            slot.flags.reset(0x10);
        }
    }
}

}  // namespace uking
