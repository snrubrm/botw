#include "Game/UI/uiNormalMap.h"
#include "KingSystem/Resource/resHandle.h"

namespace uking::ui {

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

}  // namespace uking::ui
