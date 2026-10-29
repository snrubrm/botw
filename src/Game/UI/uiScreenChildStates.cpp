#include "KingSystem/AOC/aocManager.h"
#include <nn/g3d/ResFile.h>
#include <g3d/aglNW4FToNN.h>
#include "KingSystem/Resource/resResourceFileUtil.h"
#include "Game/UI/uiScreenChildStates.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiTraceGaugeControl.h"
#include "Game/UI/euiCapturePane.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/Sound/sndSound.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiLetterAnimControl.h"
#include "Game/UI/euiMessageString.h"
#include "KingSystem/Quest/qstQuest.h"
#include "Game/UI/uiUtils.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Scene/gameScene.h"
#include "Game/gameUnk_71008ba8d8.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/gameSaveSystem.h"
#include "Game/gameRadarMgr.h"
#include "Game/gameStageBinder.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Thread/ManagedTaskHandle.h"
#include <nn/ui2d/Pane.h>
#include <math/seadMathCalcCommon.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "Game/UI/uiManager.h"

namespace uking::ui {

// 0x71009a4330
Unk_7102479838::Unk_7102479838(eui::LayoutEx* layout) : Unk_71024746d0(layout) {}

// 0x7102479b90: the initial marker bounds (x max / min, y max / min), updated by m24.
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102479b90[4] = {631.6f, -490.0f, 250.0f, -310.0f};

// 0x71009a436c
// NON_MATCHING: same instruction set; the scheduler places the position load before the two half-size adds
// and orders the adds height-first (registers s0/s1 swapped).
void Unk_7102479838::m24(sead::Heap* heap) {
    mAngleAnimator = mLayout->createAnimatorAuto("Rotate", false);
    mMapWidget = nn::font::DynamicCast<ScreenAppMapWidget>(sub_71009B064C(0, 0));
    if (auto* pane = mLayout->GetPane()->FindPaneByName("N_PosSize_00", true)) {
        const sead::Vector2f size(pane->GetSize().width, pane->GetSize().height);
        const f32 half_w = size.x * 0.5f - 35.0f;
        const f32 half_h = size.y * 0.5f - 35.0f;
        sUnk_7102479b90[0] = pane->GetPosition().x + half_w;
        sUnk_7102479b90[1] = pane->GetPosition().x - half_w;
        sUnk_7102479b90[2] = pane->GetPosition().y + half_h;
        sUnk_7102479b90[3] = pane->GetPosition().y - half_h;
    }
    _109 = true;
}

// 0x71009a44a4: hides the pin on the base map, else moves the N_Pos_00 pane to the pin position and
// stops the angle animator; the button's hit pane gets its matrix scale reset.
void Unk_7102479838::m25() {
    if (UiSubsys1::instance()->sub_7100960DAC(0)) {
        m80();
        return;
    }
    if (UiSubsys1::instance()->sub_710096357C() && mMapWidget) {
        sub_71009A4588();
        if (auto* pane = mLayout->GetPane()->FindPaneByName("N_Pos_00", true))
            pane->SetPosition({mPosition.x, mPosition.y, 0.0f});
        mAngleAnimator->Stop(mAngle);
    }
    if (auto* pane = mButton->mHitPane)
        pane->ResetMtxScaleMaybe();
}

// 0x71009a4928
void Unk_7102479838::m39(void* button) {
    if (mButton == button && mMapWidget)
        mMapWidget->_b33c = 1;
}

Unk_7102479838::~Unk_7102479838() = default;

// 0x71009a494c
const nn::font::detail::RuntimeTypeInfo* Unk_7102479838::GetRuntimeTypeInfo() const {
    return GetRuntimeTypeInfoStatic();
}


// 0x71009b30ec
void Unk_710247ae48::m7() {
    sub_71009B30F0();
}

// 0x71009b3840
void Unk_710247ae48::m15(eui::AnimButton* button) {
    auto* screen = sead::DynamicCast<ScreenPauseMenu>(sub_7100939C5C());
    if (!screen)
        return;
    if (auto* child = sub_71009B43A4(screen, 1, 0))
        child->sub_71009B38EC(this);
}

// 0x71009b40dc
void Unk_710247ae48::m19(eui::AnimButton* button) {
    auto* screen = sead::DynamicCast<ScreenPauseMenu>(sub_7100939C5C());
    if (!screen)
        return;
    if (auto* child = sub_71009B43A4(screen, 1, 0))
        child->sub_71009B4188(this);
}

// 0x71009b43a4
Unk_710247af10* sub_71009B43A4(Screen* screen, s32 group, s32 index) {
    return nn::font::DynamicCast<Unk_710247af10>(
        nn::font::DynamicCast<ScreenChildEx>(screen->getChild(group, index)));
}

// 0x71009c5e4c
// NON_MATCHING: the original lowers the five-way switch to a jump table (0,1 -> mode A, 2 -> no-op,
// 3,4 -> mode B); clang 4 folds ours to two compares because there are only two distinct bodies.
void sub_71009C5E4C(Unk_710247d8f8* child, s32 mode) {
    switch (mode) {
    case 0:
    case 1:
        child->sub_71009C5720();
        break;
    case 2:
        break;
    case 3:
    case 4:
        child->sub_71009C5A54();
        break;
    }
}

// 0x71009c58d4
// NON_MATCHING: the original unswitches the loop on UiSubsys1::sub_7100964174 (two copies of the body);
// ours keeps one loop with the flag in a register.
void Unk_710247d8f8::sub_71009C58D4() {
    const bool on = UiSubsys1::instance()->sub_7100964174();
    for (s32 i = 0; i < 14; ++i) {
        const auto& record = _158[i];
        if (record.sub_71009C5338()) {
            _388[i]->StopDisableAnim(!on);
            _388[i]->mFlags &= 0xfff0;
        } else if (record.sub_71009C5350()) {
            if (sub_7100A9A4E8(record.sub_71009C5368() - 6)) {
                _388[i]->StopDisableAnim(true);
                _388[i]->mFlags &= 0xfff0;
            } else {
                _388[i]->StopDisableAnim(false);
                _388[i]->mFlags |= 0xf;
            }
        }
    }
}

// 0x71009c5720
void Unk_710247d8f8::sub_71009C5720() {
    ksys::ui::sub_7100EDC5F0();
    for (s32 i = 0; i < 14; ++i) {
        _388[i]->setFlag10(true);
        _400->setFlag10(true);
    }
    if (_130)
        _130->PlayFromCurrent(eui::Animator::PlayType(0), 1.0f);
    sub_71009C58D4();
    if (auto* screen = sead::DynamicCast<ScreenAppMap>(
            eui::ScreenMgr::instance()->getScreen(42)))
        screen->invokeSoundLink2Event_("mc_openStampMenu");
    if (auto* home = sead::DynamicCast<ScreenAppHome>(
            eui::ScreenMgr::instance()->getScreen(44)))
        home->sub_71009DD7A8();
    _138 = true;
}

// 0x71009c5a54
void Unk_710247d8f8::sub_71009C5A54() {
    ksys::ui::sub_7100EDC5F0();
    if (!_130)
        return;
    _130->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
    for (s32 i = 0; i < 14; ++i) {
        _388[i]->setFlag10(false);
        _400->setFlag10(false);
    }
    if (auto* home = sead::DynamicCast<ScreenAppHome>(
            eui::ScreenMgr::instance()->getScreen(44)))
        home->sub_71009DE1C8();
    _138 = false;
}

// 0x71009ed41c: the original calls this out of line from every map screen function, so it is in a
// different translation unit from them.
// NON_MATCHING: the original runs the ScreenChildEx cast twice (the second one through its cached
// static); clang folds our two identical casts into one.
ScreenChildEx* ScreenAppMap::getChildExMaybe(s32 group, s32 index) {
    return nn::font::DynamicCast<ScreenChildEx>(getChild(group, index));
}

// 0x7100a52088 (placeholder name): the ScreenShopInfo child at (group, index) if it is a
// ScreenChildEx. Kept in this TU: a static in the ScreenShopInfo TU shifts its literal pool and
// breaks the matched ScreenPauseMenuMantan::sub_7100A31FA4.
// NON_MATCHING: the original runs the cast twice (the second through a cached typeInfo) and
// addresses the cache through its GOT entry; ours uses adrp + add for the function-local static.
ScreenChildEx* ScreenShopInfo::getChildExMaybe(s32 group, s32 index) {
    auto* child = nn::font::DynamicCast<ScreenChildEx>(getChild(group, index));
    static const nn::font::detail::RuntimeTypeInfo* sTypeInfo =
        ScreenChildEx::GetRuntimeTypeInfoStatic();
    if (!child)
        return nullptr;
    if (!child->GetRuntimeTypeInfo()->IsDerivedFrom(sTypeInfo))
        return nullptr;
    return child;
}

// 0x7100963034 (placeholder name): the child of group / index of `screen` cast to ScreenChildEx, with the
// original's second cast through the cached type info
// NON_MATCHING: the original addresses the cached type info and its guard through their GOT entries; ours uses
// adrp + add for the function-local static.
ScreenChildEx* sub_7100963034(Screen* screen, s32 group, s32 index) {
    auto* child = nn::font::DynamicCast<ScreenChildEx>(screen->getChild(group, index));
    static const nn::font::detail::RuntimeTypeInfo* sTypeInfo =
        ScreenChildEx::GetRuntimeTypeInfoStatic();
    if (!child)
        return nullptr;
    if (!child->GetRuntimeTypeInfo()->IsDerivedFrom(sTypeInfo))
        return nullptr;
    return child;
}

// 0x71009beb44
bool sub_71009BEB44() {
    return UiSubsys1::instance()->get38ac();
}

// 0x71009bd404
Unk_710247c010::Unk_710247c010(eui::LayoutEx* layout)
    : ScreenChildEx(layout), mButtons() {
    mModeAnimator = nullptr;
    mStateAnimator = nullptr;
}

// 0x71009be238
void Unk_710247c010::m39(void* button) {
    if (!_128)
        return;
    if (_128->mId == 42)
        sub_71009BE260(static_cast<eui::ButtonBase*>(button));
    else if (_128->mId == 34)
        sub_71009BE4E8(static_cast<eui::ButtonBase*>(button));
}

// 0x71009bdd54
void Unk_710247c010::m34() {
    mController.sub_71009CC3A0();
}

// 0x71009be0c8
void Unk_710247c010::m30() {
    mController.sub_71009CC3A0();
}

// 0x71009be770
void Unk_710247c010::m82() {
    mController.sub_71009CC970();
}

Unk_710247c010::~Unk_710247c010() = default;

// 0x710098a1f4
// NON_MATCHING: the inlined FixedObjList free-list setup differs in scheduling / register allocation only.
ScreenMainScreenUnk3648::ScreenMainScreenUnk3648(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x710098a2c8
// NON_MATCHING: the inlined ScreenChild member teardown differs in scheduling only.
ScreenMainScreenUnk3648::~ScreenMainScreenUnk3648() = default;

// 0x710098a470
bool ScreenMainScreenUnk3648::m5(bool a1) {
    Entry* entry = _1f0.front();
    if (!entry)
        return false;

    const s32 state = _104;
    if (state == 0 || (u32(state - 2) <= 4 && ((state - 2) & 1) == 0)) {
        const bool ret = ScreenChild::m5(a1);
        sub_710098A5D4();
        return ret;
    }

    s32 type = entry->_0;
    s32 current = _148;
    if (current == 12)
        current = 8;
    else if (current == 13)
        current = 9;
    if (type == 12)
        type = 8;
    else if (type == 13)
        type = 9;

    if (current == type) {
        bool keep;
        switch (entry->_0) {
        case 8:
        case 9:
        case 10:
        case 12:
        case 13:
            keep = true;
            break;
        default:
            keep = false;
            break;
        }
        if (keep)
            return false;
        _130.reset();
        _1f0.erase(entry);
        if (_148 == 46)
            return false;
    } else {
        sub_710098A5D4();
    }
    ScreenChild::m6(false);
    return ScreenChild::m5(a1);
}

// 0x710098b144
void ScreenMainScreenUnk3648::m24(sead::Heap* heap) {
    _1f0.clear();
    _130.init(3.0f);
}

// 0x710098b1b4
void ScreenMainScreenUnk3648::m25() {
    if (!sub_7100AA8F30()) {
        _1a8 = false;
    } else if (!_1a8) {
        clearAndClose_(true);
        return;
    }

    switch (_388) {
    case 1:
        _388 = 2;
        break;
    case 2:
        sub_710098A5D4();
        break;
    }

    if (_104 != 7)
        return;

    bool ended;
    if (_148 == 46) {
        const f32 progress = _130.getProgress();
        ended = true;
        if (progress <= 0.01f && progress >= -0.01f)
            ended = _130.updateAndCheckEnded();
    } else {
        ended = _130.updateAndCheckEnded();
    }

    if (_1f0.size() > 0) {
        if (ended || _130.getProgress() >= 1.0f / 3.0f) {
            ScreenChild::m6(false);
            ScreenChild::m5(true);
            sub_710098A5D4();
        }
    } else if (ended) {
        clearAndClose_(true);
    }
}

// 0x710098b3bc
void ScreenMainScreenUnk3648::m16() {
    const s32 state = _104;
    if (state != 7 && !(u32(state - 1) <= 4 && ((state - 1) & 1) == 0))
        return;
    clearAndClose_(false);
}

// 0x710098b07c
void ScreenMainScreenUnk3648::sub_710098B07C() {
    if (sub_7100A9BA78(0) && (_148 | 1) == 9)
        clearAndClose_(false);
}

// 0x710098b59c
ScreenMainScreenUnk3658::ScreenMainScreenUnk3658(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x710098b710
void ScreenMainScreenUnk3658::m24(sead::Heap* heap) {
    mChangeType = mLayout->tryCreateAnimatorAuto("ChangeType", false);
    if (mChangeType)
        mChangeType->StopAtMin();
    mItemChange = mLayout->tryCreateAnimatorAuto("ItemChange", false);
    if (mItemChange)
        mItemChange->StopAtMin();
    mItemCancel = mLayout->tryCreateAnimatorAuto("ItemCancel", false);
    if (mItemCancel)
        mItemCancel->StopAtMin();
    mInvalid = mLayout->tryCreateAnimatorAuto("Invalid", false);
    if (mInvalid)
        mInvalid->StopAtMin();
    mTextureHandle = new (heap, 8) ksys::res::Handle;
    if (auto* pane = mLayout->mPane->FindPaneByName("P_Icon_00", true)) {
        mMaterial = pane->GetMaterial();
        if (mMaterial)
            eui::SetTextureInfoFromTexMap(&mTexInfo, mMaterial->GetTexMapArray()[0]);
    }
}

// 0x710098c048
void ScreenMainScreenUnk3658::m21() {
    if (mTextureHandle) {
        mTextureHandle->requestUnload();
        if (mMaterial)
            mMaterial->GetTexMapArray()[0].ReplaceTextureInfo(&mTexInfo);
    }
    _150 = -1;
    _154 = -1;
}

// NON_MATCHING: the inlined ScreenChild member teardown differs in register allocation / scheduling only.
ScreenMainScreenUnk3658::~ScreenMainScreenUnk3658() = default;

// 0x7100985eb4
Unk_7102476db8::Unk_7102476db8(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x7100986068
void Unk_7102476db8::m24(sead::Heap*) {
    mDisable = mLayout->createAnimatorAuto("Disable", false);
    if (mDisable)
        mDisable->StopAtMin();
    mZoom = mLayout->createAnimatorAuto("Zoom", false);
    if (mZoom)
        mZoom->StopAtMin();
    mInvalid = mLayout->createAnimatorAuto("InValid", false);
    if (mInvalid)
        mInvalid->StopAtMin();
    mNumOff = mLayout->createAnimatorAuto("NumOff", false);
    if (mNumOff)
        mNumOff->StopAtMin();
    mGanon = mLayout->createAnimatorAuto("Ganon", false);
    if (mGanon)
        mGanon->StopAtMin();
    mCapture = sub_7100986160(mLayout, "N_Capture_00");
}

// 0x7100986160
// Namespace is inferred from the address-neighbor UI child and its UI consumers.
eui::CapturePane* sub_7100986160(eui::LayoutEx* layout, const char* name) {
    return nn::font::DynamicCast<eui::CapturePane>(layout->mPane->FindPaneByName(name, true));
}

// 0x7100986ffc
// NON_MATCHING: the layout pointer load follows cstr() instead of preceding it.
// Source owner is unknown; address neighbors and complete callers place this UI helper here.
eui::CapturePane* sub_7100986FFC(eui::ControlBase* control, const sead::SafeString& name) {
    const char* pane_name = name.cstr();
    return nn::font::DynamicCast<eui::CapturePane>(
        control->mLayout->mPane->FindPaneByName(pane_name, true));
}

// 0x7100986240
// NON_MATCHING: the compiler combines the odd state tests into one bitset.
void Unk_7102476db8::m25() {
    if (_104 == 7 || _104 == 1 || _104 == 3 || _104 == 5)
        sub_7100986268();
}

// 0x7100986268
// NON_MATCHING: the original reloads mZoom after evaluating Stop's argument (C++14 order) and loads mInvalid's
// frame separately in each branch.
void Unk_7102476db8::sub_7100986268() {
    auto* player = act::PlayerInfo::instance()->getPlayer();
    bool zoom = false;
    bool invalid = false;
    if (player) {
        zoom = player->m184();
        if (act::sub_71008529E8())
            zoom |= player->sub_710084CDD4();
        invalid = player->m184() && !sub_7100AA7BAC(nullptr) && sub_7100A95214() < 1;
    }

    if (mDisable && mDisable->mFrame != 0)
        mDisable->StopAtMin();

    if (mZoom) {
        if (zoom) {
            mZoom->Stop(sub_7100A9B94C() * mZoom->GetFrameSize());
        } else if (mZoom->mFrame != 0 && mZoom->mRate == 0) {
            mZoom->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
        }
    }

    if (mInvalid) {
        if (invalid) {
            if (mInvalid->mFrame != mInvalid->GetFrameSize())
                mInvalid->StopAtMax();
        } else if (mInvalid->mFrame != 0) {
            mInvalid->StopAtMin();
        }
    }
}

// 0x710098640c
void Unk_7102476db8::m27() {
    if (mGanon) {
        if (ksys::gdt::getBoolByKey("IsPlayed_Demo146_0", false))
            mGanon->StopAtMax();
        else
            mGanon->StopAtMin();
    }
}

// 0x7100986480
void Unk_7102476db8::sub_7100986480(s32 count) {
    if (mNumOff && mNumOff->mFrame != mNumOff->GetFrameSize())
        mNumOff->StopAtMax();
    sead::FixedSafeString<32> text;
    text.format("%d", count);
    setWidgetString(mLayout, "T_BowNum_00", text);
    if (mCapture)
        mCapture->_db = true;
}

// 0x7100986580
void Unk_7102476db8::sub_7100986580() {
    if (!mNumOff)
        return;
    if (mNumOff->mFrame == 0.0f)
        return;
    mNumOff->StopAtMin();
}

// NON_MATCHING: the inlined ScreenChild member teardown differs in register allocation / scheduling only.
Unk_7102476db8::~Unk_7102476db8() = default;

// 0x7100986aac / 0x7100986ab4 / 0x7100986ac0
// UiSubsys1 0x71009645d0 uses these no-argument values to clamp effect scale.
// The UI namespace is source inference from that caller and the address neighbors.
f32 sub_7100986AAC() {
    return 1.0f;
}

f32 sub_7100986AB4() {
    return 0.1f;
}

f32 sub_7100986AC0() {
    return 1200.0f;
}

// 0x710098c278
Unk_7102477c30::Unk_7102477c30(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x710098c688 / 0x710098c68c: the native table overrides only these two update hooks.
void Unk_7102477c30::m24(sead::Heap*) {}
void Unk_7102477c30::m25() {}

// NON_MATCHING: the inlined ScreenChild member teardown differs in register allocation / scheduling only.
Unk_7102477c30::~Unk_7102477c30() = default;


// 0x71009bc268
Unk_710247b960::Unk_710247b960(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x71009bc2b0 (D2), 0x71009bc388 (D0)
// NON_MATCHING: inlined base teardown computes member addresses earlier.
Unk_710247b960::~Unk_710247b960() {
    _140.freeBuffer();
}

// 0x71009bc468
// NON_MATCHING: unrolled pointer-array bounds tests use equivalent comparisons.
void Unk_710247b960::m24(sead::Heap* heap) {
    _130 = mLayout->createAnimatorAuto("Level", false);
    _138 = mLayout->createAnimatorAuto("Gauge", false);
    _140.allocBuffer(3, heap, 8);
    sead::FixedSafeString<32> name;
    for (s32 i = 0; i < 3; ++i) {
        name.format("State%d", i + 1);
        _140.insert(i, mLayout->createAnimatorAuto(name.cstr(), true));
        if (auto* animator = _140.at(i))
            animator->StopAtMin();
    }
    _150.sub_7100988EF0(mLayout->findPartsLayout("Pa_SpIcon_02"));
}

// 0x71009bc874
void Unk_710247b960::sub_71009BC874() {
    m6(true);  // native return discarded
    _168 = -1;
    _16c = 0;
}


Unk_710247bcb8::Unk_710247bcb8(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x71009bcbdc
void Unk_710247bcb8::m24(sead::Heap*) {
    mNumber = mLayout->createAnimatorAuto("Num", true);
    if (mNumber)
        mNumber->StopAtMin();
    mAttention = mLayout->createAnimatorAuto("Attention", true);
    if (mAttention)
        mAttention->StopAtMin();
    mEffectIcons[0].sub_7100988EF0(mLayout->findPartsLayout("Pa_SpIcon_00"));
    mEffectIcons[1].sub_7100988EF0(mLayout->findPartsLayout("Pa_SpIcon_01"));
    mEffectIcons[2].sub_7100988EF0(mLayout->findPartsLayout("Pa_SpIcon_02"));
}

// 0x71009bcca4
// NON_MATCHING: the mAttention frame load is hoisted above the branch (the original loads it in each branch)
void Unk_710247bcb8::sub_71009BCCA4(f32 time, s32 effect, s32 level) {
    if (effect == -1)
        return;
    if (level >= 1 && (_188 != effect || _18c != level)) {
        _188 = effect;
        _18c = level;
        sub_71009BCDD0(effect, level);
    }
    const s32 seconds = sead::Mathf::ceil(time / f32(sub_7100AA946C()));
    if (_190 != seconds) {
        _190 = seconds;
        sub_7100AA3914(mLayout, "T_Timer_00", 1, seconds, -1);
    }
    if (!mAttention)
        return;
    if (time <= 300.0f) {
        if (mAttention->mFrame != f32(mAttention->GetFrameSize()))
            mAttention->StopAtMax();
    } else if (mAttention->mFrame != 0.0f) {
        mAttention->StopAtMin();
    }
}

// 0x71009bcff8: MainScreen 0x7100a1adc4 resets the status child before the next update.
void Unk_710247bcb8::sub_71009BCFF8() {
    _188 = -1;
    _18c = 0;
    _190 = -1;
    m80();
}

// 0x71009bd010
// NON_MATCHING: the compiler hoists the argument null check before the layout load.
void Unk_710247bcb8::sub_71009BD010(const eui::Animator* animator) {
    if (!mLayout || !animator)
        return;
    if (mLayout->_70)
        mLayout->_70->ContinueFrom(*animator);
}

// 0x71009bd02c
// The const spelling is inferred from this read-only loop animator query.
eui::Animator* Unk_710247bcb8::sub_71009BD02C() const {
    if (!mLayout)
        return nullptr;
    return mLayout->_70;
}

// 0x71009bd044
void Unk_710247bcb8::m29() {
    if (_190 == 0)
        _128->invokeSoundLink2Event_("mc_PlayerStatusUpEnd");
    _188 = -1;
    _18c = 0;
    _190 = -1;
}

// NON_MATCHING: the inlined ScreenChild member teardown differs in register allocation / scheduling only.
Unk_710247bcb8::~Unk_710247bcb8() = default;

// 0x71009b9b38
Unk_710247b428::Unk_710247b428(eui::LayoutEx* layout)
    : ScreenChildEx(layout), _130{}, _1a8(nullptr), _1b0{} {}


Unk_710247ae48::~Unk_710247ae48() = default;

// 0x7101e7ddcc: 70-byte rows; sub_71009B6B4C reads the two demo numbers at +2 and +4 (not defined here)
struct Unk_7101e7ddcc {
    s16 _0;
    s16 mDemoNumber;
    s16 mDemoSubNumber;
    u8 _6[0x46 - 0x6];
};
static_assert(sizeof(Unk_7101e7ddcc) == 0x46);
}  // namespace uking::ui
extern const uking::ui::Unk_7101e7ddcc sUnk_7101e7ddcc[];
namespace uking::ui {

// 0x71025d9d08 (set up by the TU initialiser 0x71009b27b4)
static sead::SafeString sUnk_71025d9d08 = "IsPlayed_Demo";
// 0x71025d9d18: the demo name prefix (the same block, 0x10 after sUnk_71025d9d08)
static sead::SafeString sUnk_71025d9d18 = "Demo";

// 0x71009b9144
const nn::font::detail::RuntimeTypeInfo* Unk_710247af10::GetRuntimeTypeInfo() const {
    return GetRuntimeTypeInfoStatic();
}

// 0x71009b6b4c
// NON_MATCHING: the original addresses the row table directly (it is TU-local there) and through the merged
// globals for sUnk_71025d9d08; the two strings swap stack slots
bool Unk_710247af10::sub_71009B6B4C(s32 index) const {
    if (index > 22)
        return false;
    sead::FixedSafeString<128> flag_name;
    const bool ballad =
        ksys::aoc::Manager::instance()->hasAoc3() && ksys::gdt::getFlag_BalladOfHeroes_Activated(false);
    const auto& row = sUnk_7101e7ddcc[ballad ? index : index + 5];
    flag_name = sead::FormatFixedSafeString<128>("%s%3d_%1d", sUnk_71025d9d08.cstr(), row.mDemoNumber,
                                                 row.mDemoSubNumber);
    // the original evaluates this check a second time and drops the result
    ksys::aoc::Manager::instance()->hasAoc3() && ksys::gdt::getFlag_BalladOfHeroes_Activated(false);
    return ksys::gdt::getBoolByKey(flag_name, false);
}

// 0x71009b88ac (placeholder name): plays the picture book memory `index` by starting its Timeline event.
// The event name is built from the demo number pair of the same table sub_71009B6B4C reads.
// NON_MATCHING: our clang gives the named FixedSafeString and the FormatFixedSafeString temporary the
// opposite stack slots (same as sub_71009B6B4C) and sinks the table row address below the name's cstr call.
void Unk_710247af10::sub_71009B88AC(s32 index) {
    if (index > 22 || !_148)
        return;

    _148->PlayAuto(1.0f);
    sead::FixedSafeString<16> demo_name;
    const bool ballad =
        ksys::aoc::Manager::instance()->hasAoc3() && ksys::gdt::getFlag_BalladOfHeroes_Activated(false);
    const auto& row = sUnk_7101e7ddcc[ballad ? index : index + 5];
    demo_name = sead::FormatFixedSafeString<128>("%s%3d_%1d", sUnk_71025d9d18.cstr(), row.mDemoNumber,
                                                 row.mDemoSubNumber);
    sub_71008BACB8(demo_name);
}

// 0x71009b4188 (placeholder name): selects the picture book record of `state` in its group, either as the
// new guide target or, when it already is the selected one, clears the guide flag. Then plays the decide sound
// on the pause menu.
void Unk_710247af10::sub_71009B4188(Unk_7102474e38* state) {
    if (!state)
        return;

    const s32 group = state->sub_7100939C68();
    const s32 index = state->sub_7100939C78();
    const s32 validGroup = u32(group) > 3 ? -1 : group;

    bool ok = false;
    if (validGroup == 3) {
        _340 = state;
        sub_71009B8A78(6);
    } else if (u32(validGroup) < 3) {
        sead::PtrArray<Unk_710247ae28>* entries;
        if (validGroup == 0)
            entries = &_2b0;
        else if (validGroup == 1)
            entries = &_2c0;
        else if (validGroup == 2)
            entries = &_2d0;
        else
            return;

        if (index < 0 || entries->size() <= index)
            return;
        Unk_710247ae28* record = (*entries)[index];
        if (!record)
            return;
        if (record->mQuest && record->mQuest->mNotPostNote && record->mQuest->_c == 2)
            return;

        _340 = state;
        if (record->mQuestIndex != mSelectedQuestIndex) {
            sub_71009B8010(group, index);
        } else if (_300) {
            UiSubsys1::instance()->sub_7100963C70();
            if (_290 > 0) {
                const u32 count = _290;
                u64 i = 0;
                do {
                    Unk_710247ae28* other = _298[i];
                    if (other->mQuestIndex == mSelectedQuestIndex)
                        other->mGuide = false;
                } while (++i != count);
            }
            mSelectedQuestIndex = -1;
            ksys::gdt::setFlag_QuestIndexSetPointGuide(-1, false);
            _300->sub_710093FEAC();
        }
        ok = true;
    }

    if (_300)
        _308 = _300->_2e4;
    if (!ok)
        return;
    if (auto* screen = sead::DynamicCast<ScreenPauseMenu>(_128))
        screen->invokeSoundLink2Event_("mc_QuestDecide");
}

// 0x71009b7a1c
void Unk_710247af10::sub_71009B7A1C(Unk_710247ae28* record) {
    sead::FixedSafeString<256> file;
    if (record->mQuest)
        record->mQuest->sub_7100FDA570(&file);
    sead::FixedSafeString<256> label;
    if (record->mQuest)
        record->mQuest->sub_7100FDA678(&label);
    eui::MessageString message;
    getMessage(file, label, &message);
    if (mQuestCaption) {
        mQuestCaption->sub_7100BD9CDC(message, 0);
        mQuestCaption->sub_7100BD9B5C();
    }
}

// 0x71009b7d88
void Unk_710247af10::sub_71009B7D88() {
    if (_300)
        _308 = _300->_2e4;
}

// 0x71009b8010 (placeholder name): selects record `index` of picture book group `group` as the guide target.
// It moves the record's guide flag: the previously selected record's flag is cleared and the selected one is
// set, then the guide index is written to the game data and the picture book is refreshed.
void Unk_710247af10::sub_71009B8010(s32 group, s32 index) {
    const s32 groupIndex = u32(group) > 3 ? -1 : group;
    const s32 validGroup = u32(groupIndex) < 3 ? groupIndex : -1;
    sead::PtrArray<Unk_710247ae28>* entries;
    if (validGroup == 0)
        entries = &_2b0;
    else if (validGroup == 1)
        entries = &_2c0;
    else if (validGroup == 2)
        entries = &_2d0;
    else
        return;

    if (index < 0 || index >= entries->size())
        return;
    Unk_710247ae28* record = (*entries)[index];
    if (!record)
        return;

    UiSubsys1::instance()->sub_71009638F0(record->mQuest);
    if (_290 > 0) {
        const u32 count = _290;
        u64 i = 0;
        do {
            Unk_710247ae28* other = _298[i];
            if (other->mQuestIndex == mSelectedQuestIndex)
                other->mGuide = false;
        } while (++i != count);
    }
    record->mGuide = true;
    mSelectedQuestIndex = record->mQuestIndex;
    ksys::gdt::setFlag_QuestIndexSetPointGuide(record->mQuestIndex, false);
    _300->sub_710093FEAC();
}

// 0x71009b87c8
void Unk_710247af10::sub_71009B87C8(Unk_710247ae28* record, eui::MessageString* out) {
    sead::FixedSafeString<256> file;
    if (record->mQuest)
        record->mQuest->sub_7100FDA570(&file);
    sead::FixedSafeString<256> label;
    if (record->mQuest)
        record->mQuest->formatQLNameKey(&label);
    getMessage(file, label, out);
}

// 0x71009b5234
void Unk_710247af10::m23(void*) {}

// 0x71009b8d58
void Unk_710247af10::m105() {
    if (_300)
        _300->sub_710093F594(true);
    _148->StopAtMin();
    _32c = 0;
}

// 0x71009b8d98
void Unk_710247af10::m106() {}

// 0x71009b8b6c: when the system window screen is closed or closing, leaves the picture book state and releases the
// state record.
// NON_MATCHING: clang 4 tests the switch's 1 / 3 arms with two compares instead of the original's `orr #2; cmp #3`,
// and materialises `this + 0x340` in a register for the merged tail store.
void Unk_710247af10::sub_71009B8B6C() {
    auto* window = sead::DynamicCast<ScreenSystemWindow00>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindow00));
    if (!window)
        return;
    if (!window->isClosedOrClosing())
        return;
    switch (sub_7100A64304()) {
    case 0:
        if (!_340)
            return;
        if (window->_36b0 == 6) {
            sub_71009B88AC(_340->sub_7100939C78());
            getStateMachine().changeState(&sUnk_71025d9960);
        } else {
            getStateMachine().changeState(&sUnk_71025d98a0);
        }
        break;
    case 1:
    case 3:
        getStateMachine().changeState(&sUnk_71025d98a0);
        break;
    default:
        return;
    }
    _340 = nullptr;
}

// 0x71009b8d9c
void Unk_710247af10::m107() {
    if (_300)
        _300->sub_710093F594(false);
}

// 0x71009b5e4c
void Unk_710247af10::m50() {
    _1b0.sub_7100A816D8();
    getStateMachine().run();
}

// NON_MATCHING: the original compares the record count with `index` twice (signed `b.le` and the pointer
// array's unsigned `b.ls`); clang folds the second test into a `ccmp` on the same compare.
// 0x71009b8580 (placeholder name): fills _348 with the caption of entry `index` of `group`'s quest records.
void Unk_710247af10::sub_71009B8580(s32 group, s32 index) {
    const s32 groupIndex = u32(group) > 3 ? -1 : group;
    const s32 validGroup = u32(groupIndex) < 3 ? groupIndex : -1;
    sead::PtrArray<Unk_710247ae28>* entries;
    if (validGroup == 0)
        entries = &_2b0;
    else if (validGroup == 1)
        entries = &_2c0;
    else if (validGroup == 2)
        entries = &_2d0;
    else
        return;

    if (index < entries->size()) {
        if (Unk_710247ae28* entry = (*entries)[index]) {
            sub_7100AA33BC(entry->mQuest, &_348);
            return;
        }
    }
    eui::MessageString empty;
    _348.assign(empty);
}

// 0x71009b9198
s32 Unk_710247af10::m108() { return 0; }

// 0x71009b8db0
void Unk_710247af10::m109() {}

// 0x71009b8db4
void Unk_710247af10::m110() {
    sub_71009B8B6C();
}

// 0x71009b8db8
void Unk_710247af10::m111() {}

// 0x71009b91a0
s32 Unk_710247af10::m112() { return 0; }

// 0x71009b8dbc
void Unk_710247af10::m113() {
    if (auto* manager = ksys::evt::Manager::instance())
        manager->_1d1b0 &= ~2u;
    if (auto* save = SaveSystem::instance())
        save->_1a50 |= 0x1000;
}

// 0x71009b8e00
void Unk_710247af10::m114() {
    if (ksys::evt::Manager::instance()->hasActiveEvent())
        return;
    _148->PlayAuto(-1.0f);
    _128->sub_7100BEB70C();
    getStateMachine().changeState(&sUnk_71025d98a0);
}

// 0x71009b8e64
void Unk_710247af10::m115() {
    if (auto* manager = ksys::evt::Manager::instance())
        manager->_1d1b0 |= 2;
    if (auto* save = SaveSystem::instance())
        save->_1a50 &= ~0x1000;
}

// 0x71009b91a8
s32 Unk_710247af10::m116() { return 0; }

// 0x71009bc05c
s32 Unk_710247b428::m108() { return 0; }

// 0x71009b9f94
bool ScreenPauseMenuUnk3b90::sub_71009B9F94(bool active) {
    if (active) {
        // Pointer virtual form retains the original state descriptor getId call.
        if (mStateMachine.getState()->getId() != (&sUnk_710261ee00)->getId())
            return false;
        mStateMachine.changeState(&sUnk_71025d9e00);
    } else {
        mStateMachine.changeState(&sUnk_710261ee00);
    }
    return true;
}

// 0x71009ba010
bool ScreenPauseMenuUnk3b90::sub_71009BA010() {
    // called through a pointer in the original (not devirtualised)
    if (mStateMachine.getState()->getId() == (&sUnk_710261ee00)->getId())
        return false;
    return mStateMachine.getState()->getId() != (&sUnk_71025d9e00)->getId();
}

// 0x71009bb3bc
// NON_MATCHING: the original keeps the second isE3DemoMode result in a callee-saved register (unused)
void Unk_710247b428::sub_71009BB3BC(bool on) {
    if (_130 && !_130->IsPlayDisableAnim())
        _130->setFlag10(on);
    if (_138 && !_138->IsPlayDisableAnim())
        _138->setFlag10(on);
    if (_140)
        _140->setFlag10(on);
    if (_148)
        _148->setFlag10(on);
    if (_150 && (!isE3DemoMode() || !_150->IsPlayDisableAnim()))
        _150->setFlag10(on);
    if (_158) {
        // discarded call: the original calls isE3DemoMode and ignores the result
        isE3DemoMode();
        if (!_158->IsPlayDisableAnim())
            _158->setFlag10(on);
    }
}

// 0x71009bb4cc
void Unk_710247b428::m105() {
    sub_71009BB3BC(true);
}

// 0x71009bb4d4
void Unk_710247b428::m106() {
    if (!_158)
        return;
    SaveSystem* save = SaveSystem::instance();
    if (!save)
        return;
    if (!_158->IsPlayDisableAnim() && save->_1a44) {
        _158->StopDisableAnim(true);
        _158->setFlag10(false);
    } else if (_158->IsPlayDisableAnim() && !save->_1a44) {
        _158->StopDisableAnim(false);
        _158->setFlag10(true);
    }
}

// 0x71009bb58c
void Unk_710247b428::m107() {
    sub_71009BB3BC(false);
}

// 0x71009bb594
void Unk_710247b428::m109() {}

// 0x71009bb598
void Unk_710247b428::m110() {
    auto* screen = sead::DynamicCast<ScreenOptionWindow>(eui::ScreenMgr::instance()->getScreen(ScreenId::OptionWindow));
    if (!screen || screen->isOpened())
        getStateMachine().changeState(&sUnk_71025d9ec0);
}

// 0x71009bb660
void Unk_710247b428::m111() {}

// 0x71009bc064
s32 Unk_710247b428::m112() { return 0; }

// 0x71009bb664
void Unk_710247b428::m113() {}

// 0x71009bb668
void Unk_710247b428::m114() {
    auto* screen = sead::DynamicCast<ScreenOptionWindow>(eui::ScreenMgr::instance()->getScreen(ScreenId::OptionWindow));
    if (screen) {
        if ((screen->_291 & 4) && _1a8) {
            if (ksys::gdt::getFlag_JumpButtonChange())
                _1a8->StopAtMax();
            else
                _1a8->StopAtMin();
        }
        if (!screen->isClosed())
            return;
    }
    getStateMachine().changeState(&sUnk_71025d9e00);
}

// 0x71009bb768
void Unk_710247b428::m115() {}

// 0x71009bc06c
s32 Unk_710247b428::m116() { return 0; }

// 0x71009bb76c
void Unk_710247b428::m117() {}

// 0x71009bb770
void Unk_710247b428::m118() {
    switch (_1c0) {
    case 0: {
        auto* screen = sead::DynamicCast<ScreenSystemWindow00>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindow00));
        if (screen && !screen->isOpened())
            return;
        break;
    }
    case 1: {
        auto* screen = sead::DynamicCast<ScreenSystemWindow01>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindow01));
        if (screen && !screen->isOpened())
            return;
        break;
    }
    }
    getStateMachine().changeState(&sUnk_71025d9f80);
}

// 0x71009bb8c8
void Unk_710247b428::m119() {}

// 0x71009bc074
s32 Unk_710247b428::m120() { return 0; }

// 0x71009bb8cc
void Unk_710247b428::m121() {}

// 0x71009bb8d0
void Unk_710247b428::m122() {
    switch (_1c0) {
    case 0: {
        auto* screen = sead::DynamicCast<ScreenSystemWindow00>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindow00));
        if (screen && !screen->isClosed())
            return;
        break;
    }
    case 1: {
        if (ScreenSystemWindow01::sub_7100A66824() && ScreenSystemWindow01::sub_7100A66760() != -1) {
            if (!_268) {
                if (auto* player = act::PlayerInfo::instance()->getPlayer()) {
                    _268 = ksys::evt::callEvent(nullptr, "Demo025_2", "Demo025_2", player->getMtx(),
                                                false, true);
                }
            }
            GameScene::resetStage(ScreenSystemWindow01::sub_7100A667EC(), true);
        }
        auto* screen = sead::DynamicCast<ScreenSystemWindow01>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindow01));
        if (screen && !screen->isClosed()) {
            if (screen->_291 & 4)
                sub_71009B9E10();
            return;
        }
        break;
    }
    }
    getStateMachine().changeState(&sUnk_71025d9e00);
}

// 0x71009bbad0
void Unk_710247b428::m123() {}

// 0x71009bc07c
s32 Unk_710247b428::m124() { return 0; }

// 0x71009bbad4
void Unk_710247b428::m125() {}

// 0x71009bbad8
void Unk_710247b428::m126() {
    auto* screen = sead::DynamicCast<ScreenControllerWindow>(eui::ScreenMgr::instance()->getScreen(ScreenId::ControllerWindow));
    if (!screen || screen->isOpened())
        getStateMachine().changeState(&sUnk_71025da040);
}

// 0x71009bbba0
void Unk_710247b428::m127() {}

// 0x71009bc084
s32 Unk_710247b428::m128() { return 0; }

// 0x71009bbba4
void Unk_710247b428::m129() {}

// 0x71009bbcb0
void Unk_710247b428::m131() {}

// 0x71009bc08c
s32 Unk_710247b428::m132() { return 0; }

// 0x71009bbcb4
void Unk_710247b428::m133() {}

// 0x71009bbcb8
void Unk_710247b428::m134() {
    auto* screen = sead::DynamicCast<ScreenDLCWindow>(eui::ScreenMgr::instance()->getScreen(ScreenId::DLCWindow));
    if (!screen || screen->isOpened())
        getStateMachine().changeState(&sUnk_71025da100);
}

// 0x71009bbba8
void Unk_710247b428::m130() {
    auto* screen = sead::DynamicCast<ScreenControllerWindow>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::ControllerWindow));
    if (screen) {
        if ((screen->_291 & 4) && _1b0) {
            if (Manager::instance()->sub_7100A7F918())
                _1b0->StopAtMax();
            else
                _1b0->StopAtMin();
        }
        if (!screen->isClosed())
            return;
    }
    getStateMachine().changeState(&sUnk_71025d9e00);
}

// 0x71009bbd80
void Unk_710247b428::m135() {}

// 0x71009bc094
s32 Unk_710247b428::m136() { return 0; }

// 0x71009bbd84
void Unk_710247b428::m137() {}

// 0x71009bbd88
void Unk_710247b428::m138() {
    auto* screen = sead::DynamicCast<ScreenDLCWindow>(eui::ScreenMgr::instance()->getScreen(ScreenId::DLCWindow));
    if (!screen || screen->isClosed())
        getStateMachine().changeState(&sUnk_71025d9e00);
}

// 0x71009bbe50
void Unk_710247b428::m139() {}

// 0x71009bc09c
s32 Unk_710247b428::m140() { return 0; }

// 0x71009bbe54
void Unk_710247b428::m141() {}

// 0x71009bbe58
void Unk_710247b428::m142() {
    if (_1c8.sub_7100A83EC0())
        getStateMachine().changeState(&sUnk_71025d9e00);
}

// 0x71009bbe98
void Unk_710247b428::m143() {}

// 0x71009bc0a4
s32 Unk_710247b428::m144() { return 0; }

// 0x71009bbe9c
void Unk_710247b428::m145() {}

// 0x71009bbea0
void Unk_710247b428::m146() {
    auto* screen = sead::DynamicCast<ScreenSystemWindow00>(eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindow00));
    if (!screen || screen->isOpened())
        getStateMachine().changeState(&sUnk_71025da220);
}

// 0x71009bbf68
void Unk_710247b428::m147() {}

// 0x71009bc0ac
s32 Unk_710247b428::m148() { return 0; }

// 0x71009bbf6c
void Unk_710247b428::m149() {}

// 0x71009bbf70
void Unk_710247b428::m150() {
    auto* screen = sead::DynamicCast<ScreenSystemWindow00>(eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindow00));
    if (!screen || screen->isClosed()) {
        getStateMachine().changeState(&sUnk_71025d9e00);
        return;
    }
    if (!sub_7100A64304())
        createTitleStageBinder(true, true);
}

// 0x71009bc054
void Unk_710247b428::m151() {}

// 0x71009bc0b4
s32 Unk_710247b428::m152() { return 0; }

// 0x71009ba09c
void Unk_710247b428::m24(sead::Heap*) {
    _160 = mLayout->findPartsLayout("Pa_AllTips_00");
    if (_160) {
        _168 = _160->tryCreateAnimatorAuto("Type", true);
        if (_168)
            _168->StopAtMin();
        _170 = _160->tryCreateAnimatorAuto("OpenL", true);
        _178 = _160->tryCreateAnimatorAuto("OpenZR", true);
        _180 = _160->tryCreateAnimatorAuto("OpenR", true);
        _188 = _160->tryCreateAnimatorAuto("OpenY", true);
        _190 = _160->tryCreateAnimatorAuto("OpenPlusMinus", true);
        _198 = _160->tryCreateAnimatorAuto("OpenCrossKey", true);
        _1a0 = _160->tryCreateAnimatorAuto("OpenRStickPress", true);
        _1a8 = _160->tryCreateAnimatorAuto("Option", true);
    }
    getStateMachine().startState(&sUnk_710261ee00);
}

// 0x71009ba1d8
void Unk_710247b428::m25() {
    _1c8.sub_7100A83334();
    getStateMachine().run();
}

// 0x71009b9d30
void Unk_710247b428::sub_71009B9D30() {
    _130 = static_cast<eui::AnimButton*>(sub_71010A9008(0x4d));
    _138 = static_cast<eui::AnimButton*>(sub_71010A9008(0x4e));
    _140 = static_cast<eui::AnimButton*>(sub_71010A9008(0x4f));
    _148 = static_cast<eui::AnimButton*>(sub_71010A9008(0x50));
    _150 = static_cast<eui::AnimButton*>(sub_71010A9008(0x51));
    _158 = static_cast<eui::AnimButton*>(sub_71010A9008(0x52));
    if (_148) {
        _1b0 = _148->mLayout->createAnimatorAuto("New", false);
        if (_1b0)
            _1b0->StopAtMin();
    }
    if (_150) {
        _1b8 = mLayout->createAnimatorAuto("DLCbtn", true);
        if (_1b8)
            _1b8->StopAtMax();
    }
}

// 0x71009b9e10
void Unk_710247b428::sub_71009B9E10() {
    if (isE3DemoMode()) {
        if (_130)
            _130->StopDisableAnim(true);
        if (_138)
            _138->StopDisableAnim(true);
        if (_150)
            _150->StopDisableAnim(true);
        if (_158)
            _158->StopDisableAnim(true);
        return;
    }
    if (_138)
        _138->StopDisableAnim(true);
    SaveSystem* save = SaveSystem::instance();
    if (!save)
        return;
    if (save->sub_7100914DA0(0)->_300 || save->sub_7100914DA0(1)->_300 ||
        save->sub_7100914DA0(2)->_300 || save->sub_7100914DA0(3)->_300 ||
        save->sub_7100914DA0(4)->_300 || save->sub_7100914DA0(5)->_300 ||
        save->sub_7100914DA0(6)->_300 || save->sub_7100914DA0(7)->_300) {
        if (_138)
            _138->StopDisableAnim(false);
    }
    if (_158 && save->_1a44)
        _158->StopDisableAnim(true);
}

Unk_710247b428::~Unk_710247b428() = default;

// NON_MATCHING: the compiler merges the ten zero pointer stores into a memset; the original keeps them as stp pairs.
// 0x71009c96a4
Unk_710247e468::Unk_710247e468(eui::LayoutEx* layout) : ScreenChildEx(layout) {
    _130 = nullptr;
    _138 = nullptr;
    _140 = nullptr;
    _148 = nullptr;
    _150 = nullptr;
    mTexPatterns[0] = nullptr;
    mTexPatterns[1] = nullptr;
    mTexPatterns[2] = nullptr;
    mTexPatterns[3] = nullptr;
    mTexPatterns[4] = nullptr;
    _180 = ksys::world::Climate(-1);
    _184 = ksys::world::Climate(0);
    _188 = false;
    _18a = false;
}

// 0x71009c9878
void Unk_710247e468::m24(sead::Heap*) {
    _130 = mLayout->tryCreateAnimatorAuto("Scroll", false);
    if (_130)
        _130->StopAtMin();
    _138 = mLayout->tryCreateAnimatorAuto("Reload", false);
    if (_138)
        _138->StopAtMin();
    _140 = mLayout->tryCreateAnimatorAuto("Next", false);
    if (_140)
        _140->StopAtMax();
    _148 = mLayout->tryCreateAnimatorAuto("Off", false);
    if (_148)
        _148->StopAtMax();
    _150 = mLayout->tryCreateAnimatorAuto("TexPattern1", false);
    for (s32 i = 0; i < 5; ++i) {
        sead::FormatFixedSafeString<16> name("TexPattern%d", i + 2);
        mTexPatterns[i] = mLayout->tryCreateAnimatorAuto(name.cstr(), false);
    }
}

// 0x71009c9a7c
void Unk_710247e468::m25() {
    getStateMachine().run();
}

// 0x71009c9a84
void Unk_710247e468::m31() {
    sub_71009C9A88();
}

// 0x71009c9a88
// NON_MATCHING: bool spill normalization, call scheduling and static x_7 receiver elision.
void Unk_710247e468::sub_71009C9A88() {
    if (_130) {
        const f32 time = ksys::world::Manager::instance()->getWeatherMgr()->getTime();
        const auto frame_size = _130->GetFrameSize();
        _130->Stop(time * frame_size);
    }
    sub_71009C9D5C(false);
    if (_138)
        _138->StopAtMin();
    if (_140)
        _140->StopAtMax();
    if (_148)
        _148->StopAtMax();
    auto* weather = ksys::world::Manager::instance()->getWeatherMgr();
    const auto climate = ksys::world::Manager::instance()->getCurrentClimate();
    const bool state = weather->x_8();
    weather->x_7();
    _180 = climate;
    _184 = climate;
    _188 = state;
    _189 = state;
    getStateMachine().changeState(&sUnk_71025dbb28);
}

// 0x71009c9bb8
void Unk_710247e468::m27() {
    if (!sub_71009C9BEC())
        sub_71009C9A88();
}

// 0x71009c9bec
// NON_MATCHING: lookup/return folding, register allocation and static x_7 receiver elision (372 vs 364 bytes).
bool Unk_710247e468::sub_71009C9BEC() {
    for (s32 i = 0; i < 5; ++i) {
        if (!mTexPatterns[i])
            return true;
        const u8 weather = ksys::world::Manager::instance()->getWeatherMgr()->x_6(i);
        bool found = false;
        f32 frame = 0.0f;
        for (s32 j = 0; j < sUnk_71025dbcc8.size(); ++j) {
            const auto& record = sUnk_71025dbcc8[j];
            if (record.weather == weather) {
                frame = record.frame;
                found = true;
                break;
            }
        }
        if (!found)
            return false;
        if (sead::Mathf::equalsEpsilon(frame, 2.0f) &&
            ksys::world::Manager::instance()->getWeatherMgr()->x_7())
            frame = 4.0f;
        else if (frame < 0.0f)
            return false;
        if (mTexPatterns[i]->mFrame != frame)
            return false;
    }
    return true;
}

// 0x71009c9f20
// NON_MATCHING: condition folding, flag-store scheduling and register allocation (600 vs 700 bytes).
bool Unk_710247e468::sub_71009C9F20() {
    auto* weather = ksys::world::Manager::instance()->getWeatherMgr();
    const auto climate = ksys::world::Manager::instance()->getCurrentClimate();
    const bool state = weather->x_8();
    const bool cold = weather->x_7();
    const bool changed = (climate != _180) | (state != _188);
    const bool cold_changed = cold != _18a;
    _184 = _180;
    _180 = climate;
    _189 = _188;
    _188 = state;
    _18b = _18a;
    _18a = cold;
    if (cold_changed) {
        for (auto* animator : mTexPatterns) {
            if (animator && (sead::Mathf::equalsEpsilon(animator->mFrame, 2.0f) ||
                             sead::Mathf::equalsEpsilon(animator->mFrame, 4.0f)))
                return true;
        }
    }
    return changed;
}

// 0x71009ca1dc
void Unk_710247e468::m105() {}

// 0x71009ca1e0
void Unk_710247e468::m106() {
    if (sub_71009C9F20()) {
        getStateMachine().changeState(&sUnk_71025dbb88);
        return;
    }
    if (!_130)
        return;
    const f32 previous_frame = _130->mFrame;
    const f32 time = ksys::world::Manager::instance()->getWeatherMgr()->getTime();
    const f32 frame = time * _130->GetFrameSize();
    _130->Stop(frame);
    if (frame < previous_frame) {
        sub_71009C9D5C(true);
        if (_140)
            _140->Play(eui::Animator::PlayType(0), 1.0f);
    }
}

// 0x71009ca2c8
void Unk_710247e468::m107() {}

// 0x71009ca2cc
void Unk_710247e468::m109() {
    if (_138)
        _138->Play(eui::Animator::PlayType(0), 1.0f);
}

// 0x71009ca2ec
void Unk_710247e468::m110() {
    if (!_138 || _138->mRate != 0.0f)
        return;
    sub_71009C9D5C(false);
    getStateMachine().changeState(&sUnk_71025dbb28);
}

// 0x71009ca340
void Unk_710247e468::m111() {
    _138->Play(eui::Animator::PlayType(0), -1.0f);
}

// 0x71009ca35c
s32 Unk_710247e468::m108() { return 0; }

// 0x71009ca364
s32 Unk_710247e468::m112() { return 0; }

Unk_710247e468::~Unk_710247e468() = default;

// 0x71025dac60: the radar entry's animator names (the Buffer is at +0x180; the rest is its state)
struct alignas(16) Unk_71025dac60 {
    u8 _0[0x180];
    sead::Buffer<sead::SafeString> _180;
};
KSYS_VISIBILITY_HIDDEN Unk_71025dac60 sUnk_71025dac60;

// 0x71009c03e0: sets up the radar entry's eight animators from the reference page's animator names,
// stops them at their start and centers the first one.
void Unk_710247c368::m24(sead::Heap* heap) {
    Unk_71025d6ac0::instance()->sub_7100968040();
    for (u32 i = 0; i < 8; ++i) {
        eui::LayoutEx* layout = mLayout;
        if (layout)
            mAnimators[i] = layout->createAnimatorAuto(sUnk_71025dac60._180[i].cstr(), false);
    }
    const u16 frame_size = mAnimators[0]->GetFrameSize();
    const f32 half = f32(frame_size) * 0.5f;
    _148 = half;
    _140 = half;
    _144 = half;
    mAnimators[0]->Stop(half);
    mAnimators[1]->StopAtMin();
    mAnimators[6]->StopAtMin();
    mAnimators[7]->StopAtMin();
    _14c = 0;
    mAnimators[3]->StopAtMin();
}

// 0x71009c0310
void Unk_710247c368::sub_71009C0310() {
    if (!Unk_71025d6ac0::instance()->get88())
        return;
    Unk_71025d6ac0::instance()->clear88();
    _150 = 0;
    if (mAnimators[0])
        mAnimators[0]->StopAtMin();
    if (mAnimators[1])
        mAnimators[1]->StopAtMin();
    if (mAnimators[3])
        mAnimators[3]->StopAtMin();
    if (mAnimators[4])
        mAnimators[4]->StopAtMax();
    if (mAnimators[5])
        mAnimators[5]->StopAtMax();
    if (mAnimators[6])
        mAnimators[6]->StopAtMin();
    if (mAnimators[7])
        mAnimators[7]->StopAtMin();
}

// 0x71009c0660
void Unk_710247c368::m14() {
    Unk_71025d6ac0::instance()->sub_71009684A0();
    mAnimators[0]->Stop(_148);
    mAnimators[1]->StopAtMin();
    mAnimators[5]->StopAtMax();
    Unk_71025d6ac0::instance()->sub_7100968688();
    _14c = 0;
    mAnimators[3]->StopAtMin();
}

// 0x71009c06d8
void Unk_710247c368::m27() {
    if (!RadarMgr::instance())
        return;
    Unk_71025d6ac0::instance()->sub_71009685C4();
    switch (Unk_71025d6ac0::instance()->sub_71009682CC()) {
    case 0:
        mAnimators[2]->StopAtMin();
        break;
    case 1:
        mAnimators[2]->StopAtMax();
        break;
    }
    mAnimators[6]->StopAtMin();
    mAnimators[7]->StopAtMin();
}

// 0x71009c0770
void Unk_710247c368::m29() {
    Unk_71025d6ac0::instance()->sub_710096809C();
}

// 0x71009c0780
void Unk_710247c368::m30() {
    if (!UiSubsys1::instance()->get38b8())
        return;
    _144 = _148;
    _140 = _148;
    if (mAnimators[5])
        mAnimators[5]->StopAtMax();
    Unk_71025d6ac0::instance()->sub_7100968688();
    _14c = 0;
    mAnimators[3]->StopAtMin();
}

// 0x71009c07fc
void Unk_710247c368::sub_71009C07FC(s32 state) {
    if (!mAnimators[2])
        return;
    switch (state) {
    case 0:
        mAnimators[2]->StopAtMin();
        break;
    case 1:
        mAnimators[2]->StopAtMax();
        break;
    }
}

// inline-only in the original; name is a guess: the same SoundMgr UI-flag test is inlined three times in m25.
static bool isUiSoundFlagSet() {
    return ksys::snd::SoundMgr::instance() &&
           (ksys::snd::SoundMgr::instance()->mUiSoundMgr->_80 & 0xa) != 0;
}

// 0x71009c04fc
void Unk_710247c368::m25() {
    if (Unk_71025d6ac0::instance()->sub_71009685AC(0)) {
        if (Unk_71025d6ac0::instance()->sub_71009686D8()) {
            if (mCurrentAnimator) {
                const f32 frame = mCurrentAnimator->mFrame;
                if (frame == f32(mCurrentAnimator->GetFrameSize()))
                    Unk_71025d6ac0::instance()->sub_71009686AC();
            }
            Unk_71025d6ac0::instance()->sub_71009686E8();
            return;
        }
        if (isUiSoundFlagSet()) {
            Unk_71025d6ac0::instance()->sub_71009686C8();
            if (!Unk_71025d6ac0::instance()->sub_71009685AC(0) || !mCurrentAnimator) {
                const bool swapped = Unk_71025d6ac0::instance()->sub_71009684C4();
                mCurrentAnimator = mAnimators[swapped ? 6 : 7];
            }
        }
        if (isUiSoundFlagSet()) {
            if (Unk_71025d6ac0::instance()->sub_71009684C4()) {
                Unk_71025d6ac0::instance()->sub_71009684CC(false);
                mAnimators[7]->PlayAuto(1.0f);
            } else {
                Unk_71025d6ac0::instance()->sub_71009684CC(true);
                mAnimators[6]->PlayAuto(1.0f);
            }
        }
    } else if (isUiSoundFlagSet()) {
        if (Unk_71025d6ac0::instance()->sub_71009684C4()) {
            Unk_71025d6ac0::instance()->sub_71009684CC(false);
            mAnimators[7]->PlayAuto(1.0f);
        } else {
            Unk_71025d6ac0::instance()->sub_71009684CC(true);
            mAnimators[6]->PlayAuto(1.0f);
        }
    }
    Unk_71025d6ac0::instance()->sub_71009686E8();
}

// NON_MATCHING: virtual target register allocation after the frame-size query.
// 0x71009c082c
void Unk_710247c368::sub_71009C082C() {
    Unk_71025d6ac0::instance()->sub_71009682A4();
    m6(true);  // Native virtual call discards its result.
    if (_14c == 0) {
        const f32 frame_size = mAnimators[4]->GetFrameSize();
        mAnimators[4]->Stop(frame_size - mAnimators[3]->mFrame);
    }
    mAnimators[4]->PlayFromCurrent(eui::Animator::PlayType(0), 1.0f);
    _14c = 1;
}

// NON_MATCHING: the inlined ScreenChild member teardown differs in register allocation / scheduling only.
// 0x71009bf770
Unk_710247c368::Unk_710247c368(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

Unk_710247c368::~Unk_710247c368() = default;

// 0x7100986868
Unk_7102477110::Unk_7102477110(eui::LayoutEx* layout) : ScreenChildEx(layout), _160() {
    for (auto& value : _160._0)
        value = 0;
}

// 0x71009868f4
// NON_MATCHING: the inlined ScreenChild member teardown differs in scheduling only.
Unk_7102477110::~Unk_7102477110() {
    for (auto& entry : _160.effects)
        entry.handle.kill();
    _3f0.freeBuffer();
}

namespace {
// The guide text records of the main screen child, the sead::Buffer at 0x71025d7ec0 + 0x160 that the TU
// initialiser 0x71009866c0 fills with the three message ids below (values 6 / 0x1c / 0xb).
struct GuideTextRecord {
    s32 value;
    u32 _4;
    sead::SafeString text;
};
static_assert(sizeof(GuideTextRecord) == 0x18);

struct GuideTextBlock {
    GuideTextBlock() : mRecords(3, mRecordArray) {}

    u8 _0[0x160];
    sead::Buffer<GuideTextRecord> mRecords;
    GuideTextRecord mRecordArray[3] = {
        {6, 0, sead::SafeString("0037")},
        {0x1c, 0, sead::SafeString("0038")},
        {0xb, 0, sead::SafeString("0048")},
    };
};
static_assert(offsetof(GuideTextBlock, mRecords) == 0x160);

GuideTextBlock sUnk_71025d7ec0;
}  // namespace

// NON_MATCHING: clang inlines the 184-byte sub_7100986B0C into this body (the original keeps it as a tail
// call, 64 bytes).
// 0x7100986acc
void Unk_7102477110::sub_7100986ACC() {
    Manager::instance()->sub_7100A7F900(_160.mPartsLayout->_70);
    sub_7100986B0C(_148, false);
}

// NON_MATCHING: the original duplicates the mRecords[1] load in both arms of the flag branch (184 bytes);
// clang shares one copy after the branch (160 bytes).
// 0x7100986b0c
void Unk_7102477110::sub_7100986B0C(bool flag, bool a2) {
    if (flag) {
        _298.sub_7100934308(0, sUnk_71025d7ec0.mRecords[0].text, sUnk_71025d7ec0.mRecords[0].value);
        _298.sub_7100934308(2, sUnk_71025d7ec0.mRecords[2].text, sUnk_71025d7ec0.mRecords[2].value);
    }
    const auto& record = sUnk_71025d7ec0.mRecords[1];
    _298.sub_7100934308(1, record.text, record.value);
    _298.sub_7100934478(a2);
}

// 0x7100987e84
void Unk_7102477110::m14() {}


// 0x710098fc08
// 0x71025d80ad8: hidden external so the marker TU loads it with adrp + ldr instead of folding it.
KSYS_VISIBILITY_HIDDEN AppMapIconPart* sUnk_71025D80AD8;

AppMapIconPart::AppMapIconPart(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x710099ec7c
void AppMapIconPart::m16() {
    for (auto* entry : UiSubsys1::instance()->_5d8)
        entry->m22();
}

// 0x710099e384: closes every entry of the four marker lists.
void AppMapIconPart::sub_710099E384() {
    for (auto& entry : UiSubsys1::instance()->_280)
        static_cast<UiSubsys1Entry*>(entry)->m22();
    for (auto* entry : UiSubsys1::instance()->_5d8)
        entry->m22();
    for (auto* entry : UiSubsys1::instance()->_620)
        entry->m22();
    for (auto* entry : UiSubsys1::instance()->_668)
        entry->m22();
}

// 0x7100994e98: stops both marker animations, closes their layouts and clears the current marker.
void AppMapIconPart::sub_7100994E98() {
    if (_410) {
        _410->sub_710098CFD4(-1.0f);
        if (_380) {
            _380->StopAtMin();
            if (_378)
                _378->startAnimCloseImpl_(false, true);
        }
        if (_3f8) {
            _3f8->StopAtMin();
            if (_3f0)
                _3f0->startAnimCloseImpl_(false, true);
        }
    }
    const s32 count = _2f0.size();
    _418 = nullptr;
    _410 = nullptr;
    _408 = nullptr;
    if (count != 0) {
        Unk_7102478c68* marker = _2f0(0);
        if (marker && marker->_58)
            marker->_58->StopAtMin();
    }
}

// 0x710099fd3c (placeholder name): resets the markers, then stops the first marker's animator.
void AppMapIconPart::sub_710099FD3C() {
    sub_7100994E98();
    if (_2f0.size() != 0) {
        Unk_7102478c68* marker = _2f0(0);
        if (marker && marker->_58)
            marker->_58->StopAtMin();
    }
}

// 0x710099fd8c (placeholder name): stops the first marker's animator at its maximum frame.
void AppMapIconPart::sub_710099FD8C() {
    if (_2f0.size() != 0) {
        Unk_7102478c68* marker = _2f0(0);
        if (marker && marker->_58)
            marker->_58->StopAtMax();
    }
}

// 0x7100994e88
bool AppMapIconPart::sub_7100994E88() const {
    return _410 != nullptr;
}

// 0x7100990984
UiSubsys1Entry* AppMapIconPart::getHoveredIconData() const {
    if (!_410)
        return nullptr;
    return _410->_18;
}

// NON_MATCHING: the original also reads the map screen's +0x20 pointer into a stack slot next to the
// formatted message (the pointer is not read again in the function); the rest of the body is unknown
// beyond the message assignment.
// 0x710099099c
void AppMapIconPart::m24(sead::Heap*) {
    _420 = UiSubsys1::instance();
    sUnk_71025D80AD8 = this;
    sub_7100990A64();
    _360 = _128->sub_7100A480B4("Pa_MaskBtn_00");

    sead::FormatFixedSafeString<32> message("選択中のマップアイコン");
    sead::SafeString text;
    text = message;
}

// 0x7100994374
bool AppMapIconPart::isHoveredIconChangedMaybe() const {
    if (!_410)
        return false;
    return _410 != _418;
}

// 0x7100994e68
bool AppMapIconPart::isPrevHoveredIconLostMaybe() const {
    if (!_418)
        return false;
    return _410 != _418;
}

// 0x7100993c08
void AppMapIconPart::m34() {
    for (auto* entry : UiSubsys1::instance()->_5d8)
        entry->m22();
    UiSubsys1::instance()->_5d8.clear();
    sub_7100994E98();
}

// 0x7100993bc0
void AppMapIconPart::m31() {
    sub_710099E384();
    sub_71009919CC(true);
    UiSubsys1::instance()->sub_7100960AD8();
    sub_7100991B90();
    sub_710099E49C();
}

// 0x710098fc90
// NON_MATCHING: the inlined ScreenChild member teardown differs in scheduling only.
AppMapIconPart::~AppMapIconPart() {
    sub_710098FD5C();
}

// 0x71009c37f8
// NON_MATCHING: the original stores _130 and the vtable before the zero members (scheduling only).
Unk_710247d580::Unk_710247d580(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

Unk_710247d580::~Unk_710247d580() = default;

// 0x71009c54e4
// NON_MATCHING: the original stores _130 after the _158 element ctors (just before the _388 memset).
Unk_710247d8f8::Unk_710247d8f8(eui::LayoutEx* layout) : ScreenChildEx(layout), _158() {}

Unk_710247d8f8::~Unk_710247d8f8() = default;

bool Unk_710247d8f8::sub_71009C5B68() const {
    return _138;
}

// 0x71009c69a4
Unk_710247dc90::Unk_710247dc90(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

Unk_710247dc90::~Unk_710247dc90() = default;

// 0x71009c7454
void Unk_710247dc90::m105() {
    if (mBtnL01)
        mBtnL01->setFlag10(true);
    if (mBtnR01)
        mBtnR01->setFlag10(true);
    auto* screen = _128;
    if (sead::IsDerivedFrom<ScreenAppCamera>(screen))
        screen->moveBoxCursorByButton_(mBtnR01);
}

// 0x71009c751c
void Unk_710247dc90::m106() {}

// 0x71009c7520
void Unk_710247dc90::m107() {}

// 0x71009c7524
void Unk_710247dc90::m109() {
    if (mBtnL00)
        mBtnL00->setFlag10(false);
    if (mBtnR00)
        mBtnR00->setFlag10(false);
    if (mBtnL01)
        mBtnL01->setFlag10(false);
    if (mBtnR01)
        mBtnR01->setFlag10(false);
    if (mAlbumSaveOut && mAlbumSaveOut->mRate != 0.0f)
        return;
    mContentCross->PlayAuto(1.0f);
}

// 0x71009c75d0
void Unk_710247dc90::m110() {
    if (mAlbumSaveOut && (mAlbumSaveOut->mFlags & 2))
        mContentCross->PlayAuto(1.0f);
    else if (mContentCross && (mContentCross->mFlags & 2))
        getStateMachine().changeState(&sUnk_71025db8e0);
}

// 0x71009c7618
void Unk_710247dc90::m111() {}

// 0x71009c761c
void Unk_710247dc90::m113() {
    if (mBtnL00)
        mBtnL00->setFlag10(_6f0[1] == 0);
    if (mBtnR00)
        mBtnR00->setFlag10(true);
    auto* screen = _128;
    if (sead::IsDerivedFrom<ScreenAppCamera>(screen))
        screen->moveBoxCursorByButton_(mBtnR00);
}

// 0x71009c76ec
void Unk_710247dc90::m114() {
    if (!(_128->mButtonGroup->_38 & 2))
        return;
    if (!(mBtnL00->mFlags & 0x10))
        return;
    if (!sub_71010A9064(2))
        return;
    _128->sub_71010AA894();
    mBtnL00->DownOff(false);
}

// 0x71009c7750
void Unk_710247dc90::m115() {}

// 0x71009c7754
void Unk_710247dc90::m117() {
    if (mBtnL00)
        mBtnL00->setFlag10(false);
    if (mBtnR00)
        mBtnR00->setFlag10(false);
    if (mBtnL01)
        mBtnL01->setFlag10(false);
    if (mBtnR01)
        mBtnR01->setFlag10(false);
    if (mFirstCapture && mFirstCapture->mRate != 0.0f)
        sub_7100AA86EC(1, true);
}

// 0x71009c77f8
void Unk_710247dc90::m118() {
    if ((mFirstCapture && (mFirstCapture->mFlags & 2)) ||
        (mChooseNew && (mChooseNew->mFlags & 2)) || (mChooseNow && (mChooseNow->mFlags & 2)) ||
        (mAlbumSaveOut && (mAlbumSaveOut->mFlags & 2))) {
        m6(true);
    }
}

// 0x71009c784c
void Unk_710247dc90::m119() {}

// 0x71009c7850
void Unk_710247dc90::m24(sead::Heap* heap) {
    _408.sub_71009CBD48(heap, mLayout, "P_CaptureNow_00");
    if (auto* pane = mLayout->mPane->FindPaneByName("P_CaptureNew_00", true))
        _130 = pane->GetMaterial();
    if (auto* pane = mLayout->mPane->FindPaneByName("P_Album_00", true))
        _138 = pane->GetMaterial();
    mFirstCapture = mLayout->tryCreateAnimatorAuto("FirstCapture", false);
    mChooseNow = mLayout->tryCreateAnimatorAuto("ChooseNow", false);
    mChooseNew = mLayout->tryCreateAnimatorAuto("ChooseNew", false);
    mContentCross = mLayout->tryCreateAnimatorAuto("ContentCross", false);
    mAlbumSaveOut = mLayout->tryCreateAnimatorAuto("AlbumSaveOut", false);
    if (auto* screen = sead::DynamicCast<ScreenEx>(_128)) {
        mBtnL01 = static_cast<eui::AnimButton*>(screen->sub_7100A480B4("Pa_SystemWindow_00/Pa_BtnL_01"));
        mBtnR01 = static_cast<eui::AnimButton*>(screen->sub_7100A480B4("Pa_SystemWindow_00/Pa_BtnR_01"));
        if (mBtnL01)
            mBtnL01->setFlag10(false);
        if (mBtnR01)
            mBtnR01->setFlag10(false);
        mBtnL00 = static_cast<eui::AnimButton*>(screen->sub_7100A480B4("Pa_SystemWindow_00/Pa_BtnL_00"));
        mBtnR00 = static_cast<eui::AnimButton*>(screen->sub_7100A480B4("Pa_SystemWindow_00/Pa_BtnR_00"));
        if (mBtnL00)
            mBtnL00->setFlag10(false);
        if (mBtnR00)
            mBtnR00->setFlag10(false);
    }
}

// 0x71009c7ac0
void Unk_710247dc90::m25() {
    _408.sub_71009CBE38();
    getStateMachine().run();
}

// 0x71009c7ae8
void Unk_710247dc90::m31() {
    getStateMachine().changeState(&sUnk_710261ee00);
}

// 0x71009c7af8
void Unk_710247dc90::m34() {
    getStateMachine().changeState(&sUnk_710261ee00);
}

// 0x71009c7b08
void Unk_710247dc90::m28() {
    getStateMachine().changeState(&sUnk_71025db820);
    sub_7100AA86EC(1, false);
    _128->mButtonGroup->_38 |= 2;
}

// 0x71009c7b54
void Unk_710247dc90::m29() {
    if (mBtnL00)
        mBtnL00->setFlag10(false);
    if (mBtnR00)
        mBtnR00->setFlag10(false);
    if (mBtnL01)
        mBtnL01->setFlag10(false);
    if (mBtnR01)
        mBtnR01->setFlag10(false);
    sub_7100AA86EC(1, true);
}

// 0x71009c7bd8
void Unk_710247dc90::m30() {
    _408.sub_71009CC3A0();
}

// 0x71009c7d7c
void Unk_710247dc90::m40(void*) {
    _128->mButtonGroup->_38 |= 2;
}

// 0x71009c7d94
void Unk_710247dc90::m82() {
    _408.sub_71009CC970();
}

// 0x71009c7da0
s32 Unk_710247dc90::m108() {
    return 0;
}

// 0x71009c7da8
s32 Unk_710247dc90::m112() {
    return 0;
}

// 0x71009c7db0
s32 Unk_710247dc90::m116() {
    return 0;
}

// 0x71009c7db8
s32 Unk_710247dc90::m120() {
    return 0;
}

// 0x71009c81cc
// NON_MATCHING: the original stores 0x1ac / 0x1b4 before the memset of 0x130 and orders the later stores differently.
Unk_710247e0c8::Unk_710247e0c8(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

Unk_710247e0c8::~Unk_710247e0c8() = default;

// 0x710099ee8c (placeholder name): whether the map state's 0x3888 value is 1
bool AppMapIconPart::sub_710099EE8C() const {
    return _420 ? _420->is3888Equal(1) : false;
}

// inline-only in the original; name is a guess (the same by-value kind test repeats in
// sub_710099EDC0 and UiSubsys1Entry::m13).
static inline bool isIconKind(UiSubsys1Entry::Kind kind, UiSubsys1Entry::Kind other) {
    return int(kind) == int(other);
}

// 0x710099eea0 (placeholder name): whether the hovered icon's kind is 21 or 22
// NON_MATCHING: our clang stores the two Kind arguments of the first test with one stp and swaps their
// stack slots ([sp,#8] / [sp,#0xc]); the original stores the constant at [sp,#0xc] and the member copy at
// [sp,#8] separately.
bool AppMapIconPart::sub_710099EEA0() const {
    if (!_410)
        return false;
    UiSubsys1Entry* entry = _410->_18;
    if (!entry)
        return false;
    if (isIconKind(entry->_20, UiSubsys1Entry::Kind(21)))
        return true;
    return isIconKind(entry->_20, UiSubsys1Entry::Kind(22));
}

// 0x710099ef78 (placeholder name): the map icon mode body of modes 0 and 1. Mode 0 drops the hovered
// marker and parks both panes at its entry's position (or at the subsystem position when no marker is
// hovered); mode 1 moves the panes to the entry and records its pin.
// NON_MATCHING: the pin's id load and the UiSubsys1 pointer load are swapped (the original evaluates the
// argument before the object, which C++17 sequences the other way round).
void sub_710099EF78(AppMapIconPart* self) {
    if (self->_420->is38e0Equal(0)) {
        if (self->_410) {
            self->_410->sub_710098CFD4(-1.0f);
            if (self->_408 && self->_408->_18) {
                auto* entry = self->_408->_18;
                if (self->_378) {
                    const nn::util::Float3 position{entry->_34.x, entry->_34.y, 0.0f};
                    self->_378->mPane->SetPosition(position);
                }
                if (self->_3f0) {
                    const nn::util::Float3 position{entry->_34.x, entry->_34.y, 0.0f};
                    self->_3f0->mPane->SetPosition(position);
                }
            }
        } else {
            const sead::Vector2f* pos = self->_420->getVec3878();
            const nn::util::Float3 position{pos->x, pos->y, 0.0f};
            if (self->_378)
                self->_378->mPane->SetPosition(position);
            if (self->_3f0)
                self->_3f0->mPane->SetPosition(position);
        }
    } else if (self->_420->is38e0Equal(1)) {
        if (!self->_410)
            return;
        if (auto* entry = self->_410->_18) {
            if (self->_378) {
                const nn::util::Float3 position{entry->_34.x, entry->_34.y, 0.0f};
                self->_378->mPane->SetPosition(position);
            }
            if (self->_3f0) {
                const nn::util::Float3 position{entry->_34.x, entry->_34.y, 0.0f};
                self->_3f0->mPane->SetPosition(position);
            }
        }
        if (auto* entry = self->_410->_18) {
            const s32 id = entry->_1c;
            const s32 index = self->_420->sub_710096349C(UiSubsys1::Pin(id));
            self->_420->set38e8(index);
        }
    }
    self->_408 = nullptr;
}

// 0x71009f490 (placeholder name): the map icon mode 3 body.
// NON_MATCHING: two block-shape differences. The three frame ranges collapse into one `frame - 0xf < 0xb`
// test plus a select (the original keeps every range separate), and the kind test folds to `kind - 0x15 <=
// 1` (the original compares the kind and the temporary through stack slots). The rest matches. The pin index comes from the frame of the
// animator _390 (three frame ranges map to 0..5, 6..10 and 11..13, otherwise -1); mode 0 hands the position
// of the selected entry (or the subsystem position) to the pin widget, mode 1 also records the pin and
// resets the two animators outside the 6..10 range.
void sub_71009F490(AppMapIconPart* self) {
    s32 index = -1;
    if (self->_390) {
        const s32 frame = s32(self->_390->mFrame);
        if (u32(frame - 0xf) < 6) {
            index = frame - 0xf;
        } else if (u32(frame - 0x15) <= 4) {
            index = frame - 0x15 + 6;
        } else if (u32(frame - 0x22) < 4) {
            index = frame - 0x22 + 11;
        }
    }
    if (self->_420->is38e0Equal(0)) {
        sead::Vector2f position;
        if (self->_410) {
            if (self->_410->_18)
                position = self->_410->_18->_34;
        } else {
            position = *self->_420->getVec3878();
        }
        self->_420->sub_7100964518(index, position, false);
    } else if (self->_420->is38e0Equal(1)) {
        if (self->_410 && self->_410->_18) {
            auto* entry = self->_410->_18;
            const sead::Vector2f position = entry->_34;
            const auto kind = entry->_20;
            if (kind == UiSubsys1Entry::Kind(0x15) || kind == UiSubsys1Entry::Kind(0x16)) {
                entry->sub_7100951388(false);
                UiSubsys1::instance()->sub_71009645A0();
            }
            self->_420->sub_7100964518(index, position, true);
            self->_420->set38f4(index);
        }
    }
    if (u32(index - 6) >= 5) {
        if (self->_388)
            self->_388->PlayAuto(1.0f);
        if (self->_400)
            self->_400->PlayAuto(1.0f);
    }
    self->_420->set38ec(self->_420->get38e0(), 3);
}

// 0x710099edc0 (placeholder name): the map icon mode 4 body. When the hovered marker is a shrine / tower
// (kinds 0x15 / 0x16), disables its pin and refreshes the selected marker.
// NON_MATCHING: clang folds the two Kind comparisons into a kind - 0x15 <= 1 range test; the original
// keeps the Kind local and each temporary in stack slots.
void sub_710099EDC0(AppMapIconPart* self) {
    auto* entry = self->getHoveredIconData();
    if (!entry)
        return;
    const auto kind = entry->_20;
    if (kind == UiSubsys1Entry::Kind(0x15) || kind == UiSubsys1Entry::Kind(0x16)) {
        entry->sub_7100951388(false);
        UiSubsys1::instance()->sub_71009645A0();
    }
}

// 0x710099ef18 (placeholder name): the map icon mode dispatcher. Modes 0 and 1 share the first body.
void sub_710099EF18(AppMapIconPart* self, s32 mode) {
    switch (mode) {
    case 0:
    case 1:
        sub_710099EF78(self);
        break;
    case 2:
        sub_71009F0F0(self);
        break;
    case 3:
        sub_71009F490(self);
        break;
    case 4: {
        UiSubsys1* subsys = self->_420;
        subsys->set38ec(subsys->get38e0(), 4);
        break;
    }
    }
}

// 0x71009b5f80 (placeholder name): takes the picture book group index and unloads the texture slot
void Unk_710247af10::sub_71009B5F80() {
    if (_300) {
        _308 = _300->_2e4;
        _1b0.unload(0);
        _280 = -1;
        _288 = -1;
    }
}

// 0x71009b61d0
void Unk_710247af10::sub_71009B61D0() {
    if (!_300)
        return;
    _300->sub_710093FE1C();
    if (_188 == 0)
        _300->sub_710093FDCC(0);
    if (_18c == 0)
        _300->sub_710093FDCC(1);
    if (_190 == 0)
        _300->sub_710093FDCC(2);
    sub_71009B6EC0();
    if (_300)
        _300->sub_710093F594(false);
}

// 0x71009b5e1c (placeholder name): clears the selected group and the four +0x30c pointers
void Unk_710247af10::sub_71009B5E1C() {
    _1a8 = nullptr;
    _308 = -1;
    _30c = sead::Vector2f(0, 0);
    _314 = sead::Vector2f(0, 0);
    _31c = sead::Vector2f(0, 0);
    _324 = sead::Vector2f(0, 0);
}

// 0x71009c83c0 (placeholder name): stores the two gauges and applies `flag` to their +0x6c byte
void Unk_710247e0c8::sub_71009C83C0(eui::TraceGaugeControl* first, eui::TraceGaugeControl* second,
                                   bool flag) {
    _160 = first;
    _170 = second;
    if (first)
        first->_6c = flag;
    if (_170)
        _170->_6c = flag;
    _1a8 = flag;
}

// 0x71009c9420
void Unk_710247e0c8::sub_71009C9420() {
    _1c8 = nullptr;
    _1d0 = nullptr;
    _1d8 = 2;
    _1dc = 0;
    _1e0 = false;
}

// 0x71009c9438
void Unk_710247e0c8::sub_71009C9438(f32 value, s32 count) {
    _1ac = value;
    _1c0 = count;
    _1c4 |= 1;
}

// 0x71009c9450
void Unk_710247e0c8::sub_71009C9450(f32 x, f32 y) {
    _1b0.x = x;
    _1b0.y = y;
    _1c4 |= 2;
}

// NON_MATCHING: the original floors through an int / float round trip with a negative fix-up (our
// sead::Mathf::floor compares the float), and the flag store is scheduled after the second call
// 0x71009c9468
void Unk_710247e0c8::sub_71009C9468(s32 hot_level, s32 cold_level) {
    _1b0.x = sead::Mathi::clamp(sead::Mathf::floor(getResistHotVal(hot_level)), -40, 80);
    _1c4 |= 2;
    _1b0.y = sead::Mathi::clamp(sead::Mathf::floor(getResistColdVal(cold_level)), -40, 80);
}

// 0x71009c9540
void Unk_710247e0c8::sub_71009C9540(s32 value) {
    _1b8 = value;
    _1c4 |= 4;
}

// 0x71009c9554
void Unk_710247e0c8::sub_71009C9554(s32 value) {
    _1bc = value;
    _1c4 |= 8;
}

// 0x71009c9568
void Unk_710247e0c8::sub_71009C9568() {
    if (!_1a8)
        _1c4 |= 0x10;
}

// 0x71009c9580
void Unk_710247e0c8::sub_71009C9580() {
    _1c4 |= 0x20;
}

}  // namespace uking::ui

// 0x71009ca980
Unk_710247e8c0::Unk_710247e8c0() = default;

Unk_710247e8c0::~Unk_710247e8c0() = default;

bool Unk_710247e8c0::m2_() {
    return _58;
}

void Unk_710247e8c0::onDestroy_() {
    if (!_50)
        return;
    _50->ReleaseTexture();
    agl::g3d::ResFile::Cleanup(_50);
    ksys::res::sub_7100FDDB70(_50);
    _50 = nullptr;
}

// 0x71009caef4
// NON_MATCHING: the original stores the _60 vtable before loading the cNullChar used for _b8
Unk_710247e960::Unk_710247e960() : _8(), _60(), _b8() {
    _cc = 0;
    _c8 = 8;
    _d0 = 100;
}

// 0x71009cafd4
Unk_710247e960::~Unk_710247e960() {
    _8.clear();
    _60.clear();
    _b8 = sead::SafeString();
    _c8 = 8;
    _cc = 0;
    _d0 = 100;
}

// NON_MATCHING: the context count and flag stores are scheduled in a different order.
// 0x71009cc648
Unk_710247e990::Unk_710247e990() = default;

// 0x71009cc7c4
Unk_710247e990::~Unk_710247e990() {
    mCommands.clear();
    mQueueState = 13;
    mPendingRequest.reset();
    mCurrentRequest.reset();
    mTaskHandle = nullptr;
}

Unk_710247b2c8::~Unk_710247b2c8() = default;

// 0x71009b8fdc
void Unk_710247b2c8::m4() {
    sub_71009B7414();
    sub_71009B2C38();
}

// 0x71009b9000
void Unk_710247b2c8::m5() {
    sub_71009B2DB4();
}

// 0x71009b9008
void Unk_710247b2c8::m7() {
    _18->sub_710093FEAC();
}

// 0x71009b2d8c
void Unk_710247b2c8::m9() {
    sub_71009B2DB4();
    _18->sub_710093F594(false);
}

// 0x71009b9010
void* Unk_710247b2c8::m10() {
    return _18->_328;
}

// The picture book entry setup for this unit type (template in uiScreens.h)
// 0x71009b91b0
template void uking::ui::ScreenAppPictureBookUnk::setupEntry<uking::ui::Unk_7102474e38>(
    sead::Heap* heap, s32 index, const uking::ui::ScreenAppPictureBookEntry::Params& params);
// 0x71009b6df0
template void uking::ui::ScreenAppPictureBookUnk::setupEntry<uking::ui::Unk_710247ae48>(
    sead::Heap* heap, s32 index, const uking::ui::ScreenAppPictureBookEntry::Params& params);
