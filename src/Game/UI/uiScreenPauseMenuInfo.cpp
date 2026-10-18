#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiScreenChildStates.h"
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

// 0x7100a2effc
void ScreenPauseMenuInfo::sub_7100A2EFFC() {
    if (_3610) {
        _3610->sub_710094BF98(0, 0);
        _3610->sub_710094BE84();
        _3618.sub_7100936254(getAnimationStep_(), false);
        _3618.sub_71009368EC(getAnimationStep_());
    }
    if (_3904) {
        _36e0.sub_71009457B4(_38f0);
        _3810.sub_71009457B4(_38f8);
        _3904 = 0;
    }
    const s32 old_heart_delta = s32(_38f4);
    const f32 hearts = sub_7100A9B6F0();
    _38f4 = _38f0 + 0.0f > hearts ? hearts - _38f0 : 0.0f;
    const f32 heart_change = f32(old_heart_delta) - _38f4;
    if (!(heart_change >= -0.0001f && heart_change <= 0.0001f) && !_3904)
        sub_7100A2DC30(_38f4);
    const s32 old_stamina_delta = s32(_38fc);
    _38fc = _38f8 < 0.0f ? 0.0f - _38f8 : 0.0f;
    const f32 stamina_change = f32(old_stamina_delta) - _38fc;
    if (!(stamina_change >= -0.0001f && stamina_change <= 0.0001f) && !_3904)
        sub_7100A2DCD8(_38fc);
    if (_391c) {
        if (_3910 != -1) {
            if (_3908) {
                _3908->sub_71009BCCA4(_3918, _3910, _3914);
                _3908->m5(true);  // native result is discarded
            }
            sub_7100A2FEDC();
            sub_7100A2E844();
        }
        _391c = 0;
    }
}



// Native parameter object 21 is Player; its EnergyTiredValue payload is at +0x1d0.
static_assert(offsetof(ksys::res::GParamListObjectPlayer, mEnergyTiredValue) == 0x1b8);

// 0x7100a31998
// NON_MATCHING: flag-update branches and saved registers differ.
void ScreenPauseMenuInfo::sub_7100A31998(f32 time, s32 effect, s32 level) {
    if (_3610) {
        if (_3610->sub_710094BE40()) {
            _3618.sub_7100936254(getAnimationStep_(), false);
            _3618.sub_71009368EC(getAnimationStep_());
        }
        _3610->sub_710094BD54();
    }
    if (_3904) {
        _36e0.sub_71009457B4(_38f0);
        _3810.sub_71009457B4(_38f8);
        _3900 &= 0xf3;
        _3904 = 0;
        sub_7100A2DC30(_38f4);
        sub_7100A2DCD8(_38fc);
    }
    if (!(_38f4 <= 0.01f && _38f4 >= -0.01f &&
          _38fc <= 0.01f && _38fc >= -0.01f)) {
        if (_38f4 > 0.0f)
            _3900 |= 4;
        else
            _3900 &= ~4;
        if (_38fc > 0.0f)
            _3900 |= 8;
        else
            _3900 &= ~8;
        _38f0 += _38f4;
        _38f8 += _38fc;
        _38f4 = 0.0f;
        _38fc = 0.0f;
        _3904 = 1;
        _36e0.sub_71009468E0(0.0f);
        _3810.sub_71009468E0(0.0f);
        _3900 &= ~1;
        bool below_tired = false;
        if (_3900 & 2) {
            if (auto* player = getPlayerActor(nullptr)) {
                const auto* param = player->getParam()->getRes().mGParamList->getPlayer();
                below_tired = _38f0 + _38f4 + _38f8 + _38fc < *param->mEnergyTiredValue;
            }
        }
        if (below_tired)
            _3900 |= 2;
        else
            _3900 &= ~2;
    }
    if (effect != -1) {
        _3910 = effect;
        _3914 = level;
        _3918 = time;
        _391c = 1;
    }
}

// A2CE68 supplies child 2; A2DDE4 writes the adjacent temperature and fire-level values.
static_assert(offsetof(ScreenPauseMenuInfo, _39a0) == 0x39a0);
static_assert(offsetof(ScreenPauseMenuInfo, _39b8) == 0x39b8);
static_assert(offsetof(ScreenPauseMenuInfo, _39bc) == 0x39bc);
static_assert(offsetof(ScreenPauseMenuInfo, _39e8) == 0x39e8);

// 0x7100a2fedc
// NON_MATCHING: byte-flag updates use different mask widths and register order.
void ScreenPauseMenuInfo::sub_7100A2FEDC() {
    if (!_39a0)
        return;
    sub_7100A2E510(&_39a8, &_39ac, &_39b0);
    _39a0->sub_71009C9468(_39a8, _39ac);
    _39a0->sub_71009C9568();
    s32 display = 0;
    s32 warning = 2;
    switch (_39b4) {
    case 1:
        if (getResistHotVal(_39a8) < _39b8)
            _39c0 |= 1;
        else
            _39c0 &= ~1;
        warning = (_39c0 & 1) ? 0 : 2;
        break;
    case 2:
        if (getResistColdVal(_39ac) > _39b8)
            _39c0 |= 1;
        else
            _39c0 &= ~1;
        warning = 2 - (_39c0 & 1);
        break;
    case 3:
        if (!(_39c0 & 8)) {
            if (_39b0 < _39bc) {
                _39c0 |= 1;
            } else if (!(_39c0 & 2)) {
                _39c0 &= ~1;
            } else {
                u32 flags = 0;
                sub_7100AA6040(&flags, sead::SafeString::cEmptyString);
                if (!(flags & 0x10))
                    _39c0 |= 1;
                else
                    _39c0 &= ~1;
            }
        }
        display = _39c0 & 1;
        break;
    case 4:
        if (_39c0 & 4) {
            u32 flags = 0;
            sub_7100AA6040(&flags, sead::SafeString::cEmptyString);
            if (!(flags & 8))
                _39c0 |= 1;
            else
                _39c0 &= ~1;
        }
        display = (_39c0 & 1) << 1;
        break;
    default:
        break;
    }
    _39a0->sub_71009C9540(display);
    _39a0->sub_71009C9554(warning);
}

}  // namespace uking::ui
