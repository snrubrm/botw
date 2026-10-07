#include <math/seadMathCalcCommon.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::ui {

// NON_MATCHING: scalar zero stores are scheduled differently around string initialization.
ScreenMiniGame::ScreenMiniGame()
    : _3648(nullptr), _3660(0), _3668(0), _366c(0), _3690(0), _36a8(0), _36c0(0) {
    _3658 = 0;
    _3650 = 0;
    for (auto& layout : _3610)
        layout = nullptr;
    _3688 = nullptr;
    _3680 = 0;
    _36e8 = nullptr;
    _36e0 = nullptr;
    _36d8 = 0;
}


// 0x7100a280a4
// NON_MATCHING: the original keeps the key temporary, the widget name and the text in separate stack slots
void ScreenMiniGame::sub_7100A280A4(const sead::SafeString& key) {
    _3670 = key;
    eui::LayoutEx* layout = _3610[1];
    const sead::SafeString name = "T_Num_00";
    const s32 value = ksys::gdt::getS32ByKey(sead::SafeString(_3670), false);
    sead::FormatFixedSafeString<32> text("%d", value);
    setWidgetString(layout, name, text);
    _366c = value;
}

// 0x7100a28318
// NON_MATCHING: the original keeps the key temporary, the widget name and the text in separate stack slots
void ScreenMiniGame::sub_7100A28318(const sead::SafeString& key) {
    _36c8 = key;
    eui::LayoutEx* layout = _3610[4];
    const sead::SafeString name = "T_Num_00";
    const s32 value = ksys::gdt::getS32ByKey(sead::SafeString(_36c8), false);
    sead::FormatFixedSafeString<32> text("%d", value);
    setWidgetString(layout, name, text);
    _36c0 = value;
}

// 0x7100a28264
void ScreenMiniGame::sub_7100A28264(const sead::SafeString& key) {
    _36b0 = key;
    const f32 value = ksys::gdt::getF32ByKey(_36b0, false);
    const s32 integer = s32(value);
    _36a8 = value;
    const s32 fraction = s32((value - f32(integer)) * 10);
    sead::FormatFixedSafeString<32> text("%d%s%1d", integer, getDecimalSeparator(false), fraction);
    setWidgetString(_3610[3], "T_Num_00", text);
}

// 0x7100a2745c
bool ScreenMiniGame::openMinigameScreen(s32 index, s32) {
    _3650 |= 1 << index;
    return sub_7100A2747C(index, false);
}

// 0x7100a275ec
bool ScreenMiniGame::sub_7100A275EC(s32 index, s32) {
    _3650 &= ~(1 << index);
    if (u32(index) > 6)
        return false;
    eui::LayoutEx* layout = _3610[index];
    if (!layout)
        return false;
    if (layout->_91 == 2)
        layout->startAnimCloseImpl_(false, false);
    return true;
}

// 0x7100a28088
void ScreenMiniGame::sub_7100A28088() {
    if (_3648)
        _3648->PlayAuto(1.0f);
}

// 0x7100a283b0
void ScreenMiniGame::sub_7100A283B0(s32 a1) {
    if (!_36e0)
        return;
    u16 size = _36e0->GetFrameSize();
    f32 frame = 0.0f;
    if (a1 >= 0) {
        frame = a1;
        if (frame > f32(size))
            frame = f32(size);
    }
    _36e0->Stop(frame);
}

// NON_MATCHING: same logic; the original keeps the two comparisons as separate branches (and loads the vtable slot
// before them), clang merges them into fccmp + csel
// 0x7100a28418
void ScreenMiniGame::sub_7100A28418(s32 a1) {
    if (!_36e8)
        return;
    u16 size = _36e8->GetFrameSize();
    f32 frame = 0.0f;
    if (a1 >= 0) {
        frame = a1;
        if (frame > f32(size))
            frame = f32(size);
    }
    _36e8->Stop(frame);
    invokeSoundLink2Event_(frame > sead::Mathf::epsilon() || frame < -sead::Mathf::epsilon() ? "mc_ChallengeFailed" :
                                                                                               "mc_NewRecord");
}

}  // namespace uking::ui
