#include "KingSystem/ksysDebugInput.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/Unk_7102517d58.h"

Unk_7102517d58::Unk_7102517d58() = default;
Unk_7102517d58::~Unk_7102517d58() = default;

void Unk_7102517d58::sub_7101266EA0() {}

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
