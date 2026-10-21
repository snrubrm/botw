#include <container/seadBuffer.h>
#include <limits>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <time/seadTickTime.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiTUStatics.h"

namespace uking::ui {

// The TU's statics (static initializer 0x7100a69180), merged into the block at 0x71025f5760 after the
// uiTUStatics.h objects. The 8-byte objects sort before the Vector3f.
static sead::Vector2f sUnk_71025F5768{std::numeric_limits<f32>::max(), std::numeric_limits<f32>::max()};
static sead::TickTime sUnk_71025F5770;
static sead::TickSpan sUnk_71025F5778;
static sead::SafeString sLayoutName = "Title_00";
static sead::SafeString sUnk_71025F5970[] = {"In", "BtnNum", "VerType", "HardMode", "HardModeNow"};
static sead::Buffer<sead::SafeString> sUnk_71025F58D0(sUnk_71025F5970);
// Button tag lists (0x68 .. 0x6e) at 0x710249bd80.
static const s32 sUnk_710249BD80[] = {0x6e};
static const s32 sUnk_710249BD84[] = {0x6d};
static const s32 sUnk_710249BD88[] = {0x68};
static const s32 sUnk_710249BD8C[] = {0x68, 0x69};
static const s32 sUnk_710249BD94[] = {0x6a, 0x6b, 0x6c};
static const s32 sUnk_710249BDA0[] = {0x69, 0x6b, 0x6c};
static const s32 sUnk_710249BDAC[] = {0x68, 0x69, 0x6a, 0x6b, 0x6c};
static const s32 sUnk_710249BDC0[] = {0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e};
static sead::Buffer<const s32> sUnk_71025F58E0(sUnk_710249BDAC);
static sead::Buffer<const s32> sUnk_71025F58F0(sUnk_710249BD94);
static sead::Buffer<const s32> sUnk_71025F5900(sUnk_710249BDA0);
static sead::Buffer<const s32> sUnk_71025F5910(sUnk_710249BDC0);
static sead::Buffer<const s32> sUnk_71025F5920(sUnk_710249BD80);
static sead::Buffer<const s32> sUnk_71025F5930(sUnk_710249BD84);
static sead::Buffer<const s32> sUnk_71025F5940(sUnk_710249BD88);
static sead::Buffer<const s32> sUnk_71025F5950(sUnk_710249BD8C);
static sead::SafeString sMessageSet = "LayoutMsg/Title_00";

// 0x7100a69ba0
const char* ScreenTitle::getLayoutName_() const {
    return sLayoutName.cstr();
}

// 0x7100a6af64
void ScreenTitle::sub_7100A6AF64() {
    eui::Animator* animator = mLayout->_70;
    if (!animator)
        return;
    static constexpr s32 sBlockingScreens[] = {
        ScreenId::SystemWindow00, ScreenId::SystemWindow01, ScreenId::OptionWindow, ScreenId::AmiiboWindow,
        ScreenId::DLCWindow,      ScreenId::SaveTransferWindow, ScreenId::HardMode};
    for (const s32 id : sBlockingScreens) {
        auto* screen = eui::ScreenMgr::instance()->getScreen(id);
        if (screen && (screen->isOpened() || screen->isOpening())) {
            if (animator->mRate != 0.0f)
                animator->StopCurrent();
            return;
        }
    }
    if (animator->mRate != 0.0f)
        return;
    animator->PlayFromCurrent(eui::Animator::PlayType(1), 1.0f);
}

}  // namespace uking::ui
