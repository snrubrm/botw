#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageString.h"
#include "Game/gameSceneSubsys12.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/uiOnUiActorMgr.h"
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
// 0x7100a2dde0
void ScreenPauseMenuInfo::doDraw_(const eui::DrawInfoEx::RenderBufferInfo* info) {
    Screen::doDraw_(info);
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

// A2C890 places the control at 3b70 and leaves 3c28 for EnergyMeterDLC.
static_assert(offsetof(ScreenPauseMenuInfo, _3688) == 0x3688);
static_assert(offsetof(ScreenPauseMenuInfo, _36c0) == 0x36c0);
static_assert(offsetof(ScreenPauseMenuInfo, _3b70) == 0x3b70);
static_assert(offsetof(ScreenPauseMenuInfo, _3c28) == 0x3c28);

// 0x7100a2d8c4
// NON_MATCHING: branch layout and gauge-call argument register setup differ.
void ScreenPauseMenuInfo::m94() {
    if (mState != 1 && mState != 2)
        return;
    if (_3610) {
        _3610->sub_7100949EDC();
        _3618.sub_7100936034(getAnimationStep_());
        if (_3690) {
            if (_3610->_28 == 0) {
                if (_3690->mFrame != 0.0f)
                    _3690->StopAtMin();
            } else if (_3690->mFrame != f32(_3690->GetFrameSize())) {
                _3690->StopAtMax();
            }
        }
    }
    if (_3904 == 3) {
        if (!_36e0.sub_7100945D98() && !_3810.sub_7100945D98()) {
            _3904 = 0;
            sub_7100A2DC30(_38f4);
            sub_7100A2DCD8(_38fc);
        }
    } else if (_3904 == 2) {
        if (_3900 & 4) {
            _36e0.sub_7100945D84(true);
            _36e0.sub_7100946898();
        }
        if (_3900 & 8) {
            _3810.sub_7100945D84(true);
            _3810.sub_7100946898();
            playSound("mc_ExtraGanbari_Up", nullptr);
        }
        _3904 = 3;
    }
    _36e0.sub_7100945DB8();
    _3810.sub_7100945DB8();
    const s32 gauge_state = _36e0.sub_7100946864();
    if (_3698) {
        if (gauge_state == 2)
            _3698->Stop(1.0f);
        else if (gauge_state == 3)
            _3698->Stop(2.0f);
        else
            _3698->Stop(0.0f);
    }
    if (_391c == 2) {
        if (_3910 != -1) {
            if (_3908) {
                _3908->sub_71009BCCA4(_3918, _3910, _3914);
                _3908->m5(true);  // native result is discarded
            }
            sub_7100A2FEDC();
            sub_7100A2E844();
        }
        _391c = 0;
        invokeSoundLink2Event_("mc_StatusUp");
    }
    if (_3688) {
        const auto* mgr = OnUiActorMgr::instance();
        _3688->PlayFromCurrent(eui::Animator::PlayType(0),
                              mgr && mgr->_1f4.isOnBit(0) ? 1.0f : -1.0f);
    }
    if (_36c8 != 3 && _36c0 && _36c0->mCurrent) {
        const auto* animator = _36c0->mCurrent;
        const bool crossed = animator->mRate < 0.0f ? animator->mFrame <= 4.0f :
                                                     4.0f <= animator->mFrame;
        if (crossed) {
            sub_7100A30510(_36c8);
            _36c8 = 3;
        }
    }
    _39f8.sub_7100933BDC();
    if (_39f8._151)
        eui::Screen::x_2();
    if (_3c28->mFrame == f32(_3c28->GetFrameSize()))
        _3b70.sub_7100988620();
}

// 0x7100a300ac
void ScreenPauseMenuInfo::sub_7100A300AC() {
    if (_39e8)
        _39e8->m5(true);  // native result is discarded
    _36e0.sub_7100945C98(false);
    _3810.sub_7100945C98(false);
    if (_39a0)
        _39a0->m6(true);  // native result is discarded
    const s32 count = _39c8.size();
    for (s32 i = 0; i < count; ++i) {
        if (auto* child = _39c8[i])
            child->m6(true);  // native result is discarded
    }
    if (_3b58)
        _3b58->m6(true);  // native result is discarded
    _39f0 = 1;
}

// Tables initialized by the PauseMenuInfo startup routine at 0x7100a2c5d8.
struct PauseTabMessage {
    sead::SafeString label;
    u32 frame;
};
static PauseTabMessage sUnk_71025f06c0[] = {{"0014", 1}, {"0013", 2}, {"0012", 0}};
static sead::Buffer<PauseTabMessage> sUnk_71025f0890(sUnk_71025f06c0);
struct PauseInfoMessage {
    s32 icon;
    sead::SafeString label;
};
static PauseInfoMessage sUnk_71025f08b0[] = {
    {6, "0003"}, {6, "0002"}, {7, "0004"}, {8, "0000"}, {9, "0005"},
    {5, "0006"}, {4, "0009"}, {7, "0008"}, {6, "0015"},
};
static sead::Buffer<PauseInfoMessage> sUnk_71025f08a0(sUnk_71025f08b0);
static sead::SafeString sUnk_71025f0870 = "LayoutMsg/PauseMenuInfo_00";
static_assert(sizeof(PauseTabMessage) == 0x18);
static_assert(sizeof(PauseInfoMessage) == 0x18);

// 0x7100a30194
// NON_MATCHING: temperature-state switch and callback flag branches differ.
void ScreenPauseMenuInfo::sub_7100A30194() {
    if (_39e8)
        _39e8->m6(true);  // native return discarded
    _36e0.sub_7100946740(false, false);
    if (!(_38f8 <= 0.01f && _38f8 >= -0.01f))
        _3810.sub_7100946740(false, false);
    if (_39a0) {
        _39a0->sub_71009C9468(_39a8, _39ac);
        s32 level = 0;
        s32 state = 2;
        switch (_39b4) {
        case 1: state = (_39c0 & 1) ? 0 : 2; break;
        case 2: state = 2 - (_39c0 & 1); break;
        case 3: level = 1; break;
        case 4: level = 2; break;
        default: break;
        }
        _39a0->sub_71009C9438(_39b8, level);
        _39a0->sub_71009C9540((_39c0 & 1) ? level : 0);
        _39a0->sub_71009C9554(state);
        _39a0->sub_71009C9580();
        _39a0->m5(true);  // native return discarded
    }
    const s32 count = _39c8.size();
    for (s32 i = 0; i < count; ++i) {
        auto* child = _39c8.at(i);
        if (child && child->_168 != -1)
            sub_7100AA1CDC(child, _3908, true);
    }
    if (_3b58 && _3b68)
        _3b58->m5(true);  // native return discarded
    _39f0 = 0;
}

// 0x7100a30510
// NON_MATCHING: the original addresses the message tables from its merged-static base.
void ScreenPauseMenuInfo::sub_7100A30510(u32 mode) {
    u32 left = 3;
    u32 right = 0;
    if (mode == 0) {
        left = 2;
        right = 1;
    } else if (mode == 1) {
        left = 0;
        right = 3;
    }
    eui::MessageString message;
    getMessage(sUnk_71025f0870, sUnk_71025f0890[mode].label, &message);
    setWidgetString(mLayout, "T_Title_00", message);
    // AA0730 is called before testing mode==0 whenever left!=3; retain side effects.
    if (left == 3 || (sub_7100AA0730() && mode == 0) || GameSceneSubsys12::instance()->x()) {
        setWidgetString(mLayout, "T_LeftText_00", sead::SafeString::cEmptyString);
    } else {
        getMessage(sUnk_71025f0870, sUnk_71025f0890[left].label, &message);
        setWidgetString(mLayout, "T_LeftText_00", message);
    }
    if (right == 3 || GameSceneSubsys12::instance()->x()) {
        setWidgetString(mLayout, "T_RightText_00", sead::SafeString::cEmptyString);
    } else {
        getMessage(sUnk_71025f0870, sUnk_71025f0890[right].label, &message);
        setWidgetString(mLayout, "T_RightText_00", message);
    }
}

// 0x7100a30df0
// NON_MATCHING: the original addresses the info Buffer from its merged-static base.
void ScreenPauseMenuInfo::sub_7100A30DF0(bool flag) {
    {
        UiStringEntry entry;
        entry._0 = 2;
        entry._8.copy(sUnk_71025f08a0[2].label);
        entry._124 = sUnk_71025f08a0[2].icon;
        _39f8.sub_7100933FE0(entry);
    }
    {
        UiStringEntry entry;
        entry._0 = 5;
        entry._8.copy(sUnk_71025f08a0[5].label);
        entry._124 = sUnk_71025f08a0[5].icon;
        _39f8.sub_7100933FE0(entry);
    }
    {
        UiStringEntry entry;
        entry._0 = 4;
        entry._8.copy(sUnk_71025f08a0[4].label);
        entry._124 = sUnk_71025f08a0[4].icon;
        _39f8.sub_7100933FE0(entry);
    }
    _39f8.sub_7100934478(flag);
    if (_3b50)
        _3b50->m6(true);  // native return discarded
}

// 0x7100a31190
// NON_MATCHING: the original addresses the info Buffer and message set from its merged-static base.
void ScreenPauseMenuInfo::sub_7100A31190(bool flag) {
    {
        UiStringEntry entry;
        entry._0 = 7;
        entry._8.copy(sUnk_71025f08a0[7].label);
        entry._124 = sUnk_71025f08a0[7].icon;
        _39f8.sub_7100933FE0(entry);
    }
    _39f8.sub_7100934478(flag);
    if (_3b50) {
        eui::MessageString message;
        getMessage(sUnk_71025f0870, sUnk_71025f08a0[6].label, &message);
        setWidgetString(_3b50->mLayout, "T_Guide_00", message);
        sub_7100AA34A4(_3b50->mLayout, "T_Icon_00", sUnk_71025f08a0[6].icon);
        _3b50->m5(true);  // native return discarded
        eui::Screen::x_2();
    }
}

// 0x7100a313a8
// NON_MATCHING: the original addresses the info Buffer from its merged-static base.
void ScreenPauseMenuInfo::sub_7100A313A8(s32 page, bool flag) {
    if (page == 2) {
        UiStringEntry entry;
        entry._0 = 1;
        entry._8.copy(sUnk_71025f08a0[1].label);
        entry._124 = sUnk_71025f08a0[1].icon;
        _39f8.sub_7100933FE0(entry);
    } else if (page == 1) {
        UiStringEntry entry;
        entry._0 = 8;
        entry._8.copy(sUnk_71025f08a0[8].label);
        entry._124 = sUnk_71025f08a0[8].icon;
        _39f8.sub_7100933FE0(entry);
    }
    {
        UiStringEntry entry;
        entry._0 = 2;
        entry._8.copy(sUnk_71025f08a0[2].label);
        entry._124 = sUnk_71025f08a0[2].icon;
        _39f8.sub_7100933FE0(entry);
    }
    _39f8.sub_7100934478(flag);
}

// 0x7100a30444
// NON_MATCHING: tab-selection branches and merged-static addressing differ.
void ScreenPauseMenuInfo::sub_7100A30444(u32 mode) {
    if (_36c0) {
        auto* animator = _36c0->select(mode > 1 ? 1 : 0);
        if (animator) {
            if (mode == 0)
                animator->StopAtMin();
            else
                animator->StopAtMax();
        }
    }
    if (_36d0)
        _36d0->Stop(_36d8 * f32(sUnk_71025f0890[mode].frame));
    sub_7100A30510(mode);
    _36c8 = 3;
}

// 0x7100a306f4
// NON_MATCHING: animation branch order and merged-static addressing differ.
void ScreenPauseMenuInfo::sub_7100A306F4(s32 previous_mode, u32 mode) {
    if (_36c0) {
        u32 index = 1;
        f32 speed = 1.0f;
        if (mode == 1) {
            index = 0;
        } else if (mode == 0) {
            index = previous_mode != 1;
            speed = -1.0f;
        }
        auto* animator = _36c0->select(index);
        if (animator) {
            if (animator->mRate == 0.0f) {
                if (_36c8 != 3)
                    sub_7100A30510(_36c8);
                animator->PlayAuto(speed);
            } else {
                animator->PlayFromCurrent(eui::Animator::PlayType(0), speed);
            }
            _36c8 = mode;
        }
    }
    if (_36d0)
        _36d0->Stop(_36d8 * f32(sUnk_71025f0890[mode].frame));
}

}  // namespace uking::ui
