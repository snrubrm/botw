#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiScreenControlCreators.h"

namespace uking::ui {

// ScreenPauseMenuInfo creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_7102492320[] = {
    {"Pa_Gear_00", sub_7100A233EC, 0},
    {"Pa_PlayerStatusUp_00", sub_7100A17454, 0},
    {"Pa_TempMeter_00", sub_7100A1764C, 0},
    {"Pa_HaveNum_00", sub_7100A2C3D8, 0},
    {"Pa_SetBonus_00", sub_71009D7198, 0},
    {"Pa_RotateGuide_00", sub_71009D7198, 0},
    {"Pa_Guide_", sub_71009D7198, 1},
    {"Pa_Sp_", sub_7100A2C4D4, 1},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102492310(sUnk_7102492320);
// 0x7100a2c3a8
const sead::Buffer<const ChildControlCreatorEntry>* Unk_71024923e0::getEntries() const {
    return &sUnk_7102492310;
}

// 0x7100a2c3d8
ScreenChild* sub_7100A2C3D8(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247aa50(layout_ex);
}

// 0x7100a2c4d4
ScreenChild* sub_7100A2C4D4(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247b960(layout_ex);
}

}  // namespace uking::ui

namespace uking::ui {
// 0x7100a2dc30, 168 B
void ScreenPauseMenuInfo::sub_7100A2DC30(f32 delta) {
    if (!(delta <= 0.01f && delta >= -0.01f)) {
        _36e0.sub_710094574C(_38f0 + delta);
        _36e0.sub_71009468AC();
        if (_3900 & 1)
            _36e0.sub_7100946640(false);
    } else {
        _36e0.sub_7100945D70();
        _36e0.sub_71009468E0(0.0f);
        if (_3900 & 1)
            _36e0.sub_7100946640(true);
    }
}
// 0x7100a2dcd8, 264 B
void ScreenPauseMenuInfo::sub_7100A2DCD8(f32 delta) {
    if (!(delta <= 0.01f && delta >= -0.01f)) {
        const f32 value = _38f8 + delta;
        _3810.sub_710094574C(value);
        _3810.sub_7100945D04(value);
        _3810.sub_7100946740(false, false);
        if (_36e0.sub_71009468C0() && _36e0.sub_71009468D4() > 0.0f)
            _36e0.sub_71009468AC();
        _3810.sub_71009468AC();
    } else {
        _3810.sub_7100945D04(_38f8);
        _3810.sub_7100945D70();
        _3810.sub_71009468E0(0.0f);
        if (_38f8 <= 0.01f && _38f8 >= -0.01f)
            _3810.sub_7100945C98(false);
    }
    eui::Screen::x_2();
}
}
