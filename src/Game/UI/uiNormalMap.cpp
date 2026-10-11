#include "Game/UI/uiNormalMap.h"
#include "KingSystem/Resource/resHandle.h"

namespace uking::ui {

// 0x71009a4d24
Unk_7102479bb0::~Unk_7102479bb0() = default;

// 0x71009a4d2c
Unk_7102479bd0::~Unk_7102479bd0() {
    if (mHandle->requestedLoad())
        mHandle->requestUnload2();
    if (mHandle) {
        delete mHandle;
        mHandle = nullptr;
    }
}

// 0x71009a50a4
Unk_7102479bf0::~Unk_7102479bf0() = default;

// 0x71009a5bc8
Unk_7102479c10::~Unk_7102479c10() = default;

// 0x71009a55a0
// NON_MATCHING: conditional path-level selection uses csel instead of the original branches.
void Unk_7102479bf0::sub_71009A55A0(u32 level) {
    if (mTexture.mHandle) {
        if (mTexture.mHandle->getResource()) {
            mTexture.mState = 3;
            return;
        }
        if (mTexture.mHandle && !mTexture.mHandle->checkLoadStatus())
            return;
    }
    mTexture.mState = 1;
    sead::FixedSafeString<64> path;
    sub_71009A5670(mMapEntry, mType != 0 ? 3 : level, &path);
}

}  // namespace uking::ui
