#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiTUStatics.h"

namespace uking::ui {

// The TU's statics; the original merges them into the block at 0x71025ef2f0 (after the
// uiTUStatics.h objects). The states are external objects just before it.
// Unused 8-byte FLT_MAX object: the block holds five FLT_MAX floats where other UI TUs have three.
static sead::Vector2f sUnk_71025EF2F8{std::numeric_limits<f32>::max(), std::numeric_limits<f32>::max()};
static sead::SafeString sLayoutName = "MainShortCut_00";
// The guide panes sub_7100A1FE84 picks from.
static sead::SafeString sUnk_71025EF460[] = {"G_MainGuideR_00", "G_MainGuideL_00", "G_MainGuideL_01",
                                             "G_MainGuideR_01", "G_MainGuide_00"};
static sead::Buffer<sead::SafeString> sGuidePanes(sUnk_71025EF460);

ksys::StateTemplate<ScreenMainShortCut> sUnk_71025ef170(
    ++ksys::sUnk_71025cb4c8, "::StateID_Wait", &ScreenMainShortCut::m154, &ScreenMainShortCut::m155,
    &ScreenMainShortCut::m156, &ScreenMainShortCut::m157, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenMainShortCut> sUnk_71025ef1d0(
    ++ksys::sUnk_71025cb4c8, "::StateID_Menu", &ScreenMainShortCut::m158, &ScreenMainShortCut::m159,
    &ScreenMainShortCut::m160, &ScreenMainShortCut::m161, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenMainShortCut> sUnk_71025ef230(
    ++ksys::sUnk_71025cb4c8, "::StateID_WaitCloseMenu", &ScreenMainShortCut::m162, &ScreenMainShortCut::m163,
    &ScreenMainShortCut::m164, &ScreenMainShortCut::m165, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenMainShortCut> sUnk_71025ef290(
    ++ksys::sUnk_71025cb4c8, "::StateID_InvalidShortCut", &ScreenMainShortCut::m166, &ScreenMainShortCut::m167,
    &ScreenMainShortCut::m168, &ScreenMainShortCut::m169, &ksys::sUnk_710250bcd8);

// 0x7100a1f3cc
const char* ScreenMainShortCut::getLayoutName_() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
