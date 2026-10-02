// ActorAtk::Unk_710079e64c (TU around 0x7a0b60-0x7a1f68, separate from ActorAtk and Struct8Base).
#include "KingSystem/ActorSystem/actActorAtk.h"

namespace ksys::act {

ActorAtk::Unk_710079e64c::Unk1::Unk1() = default;

void ActorAtk::Unk_710079e64c::sub_71007A124C() {
    for (int i = 0; i < mNum; ++i) {
        auto& entry = mEntries[i];
        entry.resetFlags();
        entry._50 = 0;
        entry._54 = 0;
        entry._fc = false;
        entry._d8.reset();
        entry._e8.reset();
        entry._f8 = -1;
    }
    mNum = 0;
    _802 = 0;
}

}  // namespace ksys::act
