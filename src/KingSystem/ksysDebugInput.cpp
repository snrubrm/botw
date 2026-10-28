#include "KingSystem/ksysDebugInput.h"
#include <basis/seadRawPrint.h>
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/Unk_7102517d58.h"

Unk_7102517d58::Unk_7102517d58() = default;
Unk_7102517d58::~Unk_7102517d58() = default;

void Unk_7102517d58::sub_7101266EA0() {}

bool Unk_7102517d58::isOnBit(Id bit) const {
    return mFlags.isOnBit(int(bit));
}

void Unk_7102517d58::setBit(Id bit, bool on) {
    // The original converts the index once for a bounds check that release builds drop, then again
    // for the mask.
    const int index = bit;
    SEAD_ASSERT(u32(index) < 32);
    mFlags.changeBit(int(bit), on);
}

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(DebugInput)

void DebugInput::update() {
    if (mFlags.isOnBit(0)) {
        mLastDelta += VFR::instance()->getDeltaFrame();
        while (mLastDelta > 30.0) {
            mLastDelta -= 30.0;
        }
    }
}

}  // namespace ksys
