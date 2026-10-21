#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include <nn/ui2d/Group.h>
#include "Game/UI/uiPauseMenuDataMgr.h"
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

// 0x7100a1fe84
// NON_MATCHING: the guide loop keeps the index in a 64-bit register and loads the group container before cstr()
void ScreenMainShortCut::m93(sead::Heap* heap) {
    _3850.tryAllocBuffer(8, heap);
    _36f0.allocBuffer(5, heap);
    _38d0.sub_7100A814D8(heap, 0, 1, "MainShortCut_00Screen");
    _3628 = PauseMenuDataMgr::instance();
    _3618 = mLayout->createAnimatorAuto("Pos", true);
    if (_3618)
        _3618->StopAtMin();
    _3620 = mLayout->createAnimatorAuto("NumOff", false);
    if (_3620)
        _3620->StopAtMin();
    _3638.sub_71009C33F8(sub_7100BEAFB0("Pa_MainU_00"));
    _38d0.setMaterial(0, _3638.sub_71009C3780(), true);
    _38d0.setAnimator(0, _3638.mBreak.mLayout, "PicLoad");
    _3638.sub_71009C3580(false);
    _3638.sub_71009C3570(-1);
    _3638.sub_71009C36D0();
    _3638.sub_71009C3694();
    _3638.sub_71009C36C0();
    _36e0 = mLayout->createAnimatorAuto("ShortCutIn", true);
    if (_36e0)
        _36e0->StopAtMin();
    _3610 = mLayout->createAnimatorAuto("WeaponGuide", true);
    if (_3610)
        _3610->StopAtMin();
    for (s32 i = 0; i < 5; ++i) {
        eui::Animator* animator = mLayout->sub_7100BDD6D8(
            "ShortCutGuideIn", mLayout->_20->FindGroupByName(sGuidePanes[i].cstr()), true);
        _36f0.insert(i, animator);
        if (animator)
            animator->StopAtMin();
    }
    _3798 = mLayout->createAnimatorAuto("HoldShortCut", true);
    if (_3798)
        _3798->StopAtMin();
    _37a0 = mLayout->createAnimatorAuto("HoldShortCutBg", true);
    if (_37a0)
        _37a0->StopAtMin();
    _37a8 = mLayout->createAnimatorAuto("HoldShortCutDecide", true);
    if (_37a8)
        _37a8->StopAtMin();
    if (_3610)
        _3610->StopAtMin();
    _3728 = false;
    _3704.init(1.5f);
    getStateMachine().startState(&sUnk_710261ee98);
}

}  // namespace uking::ui
