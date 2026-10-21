#include <container/seadBuffer.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadSafeString.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageString.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiTUStatics.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

// The TU's statics (static initializer 0x7100a40900), merged into the block at 0x71025f1a50 after the
// uiTUStatics.h objects.
static sead::SafeString sLayoutName = "ReadyGo_00";
static sead::SafeString sMessageSet = "LayoutMsg/ReadyGo_00";
static sead::SafeString sUnk_71025F1BC8[] = {"0000", "0001"};
static sead::Buffer<sead::SafeString> sMessages(sUnk_71025F1BC8);

// 0x7100a40b58
// NON_MATCHING: the clamp compares and the element address are scheduled differently (3 lines)
void ScreenReadyGo::sub_7100A40B58(s32 a1) {
    const s32 last = sMessages.size() - 1;
    const s32 index = a1 < 0 ? 0 : (a1 > last ? last : a1);
    eui::MessageString message;
    getMessage(sMessageSet, sMessages(index), &message);
    setWidgetString(mLayout, "T_Go_00", message);
}

// 0x7100a40bf8
bool ScreenReadyGo::sub_7100A40BF8() {
    eui::Animator* animator = mLayout->mOpenAnimator;
    return animator && animator->mFrame >= 90.0f;
}

// 0x7100a40c24
const char* ScreenReadyGo::getLayoutName_() const {
    return sLayoutName.cstr();
}

// 0x7100a40c58
void ScreenReadyGo::m94() {
    eui::Animator* animator = mLayout->mOpenAnimator;
    if (animator && animator->mFrame == static_cast<f32>(animator->GetFrameSize()))
        close(-4);
}

}  // namespace uking::ui
