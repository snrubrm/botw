// Unk_7102459df8::Unk_710079d5a0 (TU from 0x79f600, separate from Unk_7102459df8: not inlined into it).
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"

namespace ksys::act {

Unk_7102459df8::Unk_710079d5a0::Unk1::Unk1() = default;

void Unk_7102459df8::Unk_710079d5a0::sub_710079F600() {
    for (int i = 0; i < mNum; ++i) {
        mEntries[i].resetFlags();
        mEntries[i]._50.reset();
    }
    mNum = 0;
    _582 = 0;
}

}  // namespace ksys::act
