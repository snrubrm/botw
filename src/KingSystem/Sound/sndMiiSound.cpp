#include "KingSystem/Sound/sndMiiSound.h"

namespace ksys::snd {

Unk_710251b6f0::Unk_710251b6f0() {
    mPendingName.clear();
}

void Unk_710251b6f0::requestUnloadMaybe() {
    mHandle.requestUnload();
    mState = 0;
}

}  // namespace ksys::snd
