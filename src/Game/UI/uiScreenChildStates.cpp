#include "KingSystem/AOC/aocManager.h"
#include <nn/g3d/ResFile.h>
#include <g3d/aglNW4FToNN.h>
#include "KingSystem/Resource/resResourceFileUtil.h"
#include "Game/UI/uiScreenChildStates.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiCapturePane.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiLetterAnimControl.h"
#include "Game/UI/euiMessageString.h"
#include "KingSystem/Quest/qstQuest.h"
#include "Game/UI/uiUtils.h"
#include "Game/Actor/Player/actPlayerInfo.h"
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

namespace uking::ui {

// 0x71009a4330
Unk_7102479838::Unk_7102479838(eui::LayoutEx* layout) : Unk_71024746d0(layout) {}

// 0x71009a4928
void Unk_7102479838::m39(void* button) {
    if (mButton == button && mMapWidget)
        mMapWidget->_b33c = 1;
}

Unk_7102479838::~Unk_7102479838() = default;


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


// 0x71009bc9bc
Unk_710247b960::Unk_710247b960(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

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

// 0x71009b8d58
void Unk_710247af10::m105() {
    if (_300)
        _300->sub_710093F594(true);
    _148->StopAtMin();
    _32c = 0;
}

// 0x71009b8d98
void Unk_710247af10::m106() {}

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

// 0x71009bb8c8
void Unk_710247b428::m119() {}

// 0x71009bc074
s32 Unk_710247b428::m120() { return 0; }

// 0x71009bb8cc
void Unk_710247b428::m121() {}

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

Unk_710247b428::~Unk_710247b428() = default;

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

// 0x710098fc08
// NON_MATCHING: the original stores 0x350 before the memset of 0x130.
Unk_7102478048::Unk_7102478048(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x710099ec7c
void Unk_7102478048::m16() {
    for (auto* entry : UiSubsys1::instance()->_5d8)
        entry->m22();
}

// 0x7100993c08
void Unk_7102478048::m34() {
    for (auto* entry : UiSubsys1::instance()->_5d8)
        entry->m22();
    UiSubsys1::instance()->_5d8.clear();
    sub_7100994E98();
}

// 0x7100993bc0
void Unk_7102478048::m31() {
    sub_710099E384();
    sub_71009919CC(true);
    UiSubsys1::instance()->sub_7100960AD8();
    sub_7100991B90();
    sub_710099E49C();
}

// 0x710098fc90
// NON_MATCHING: the inlined ScreenChild member teardown differs in scheduling only.
Unk_7102478048::~Unk_7102478048() {
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
        mBtnL01 = screen->sub_7100A480B4("Pa_SystemWindow_00/Pa_BtnL_01");
        mBtnR01 = screen->sub_7100A480B4("Pa_SystemWindow_00/Pa_BtnR_01");
        if (mBtnL01)
            mBtnL01->setFlag10(false);
        if (mBtnR01)
            mBtnR01->setFlag10(false);
        mBtnL00 = screen->sub_7100A480B4("Pa_SystemWindow_00/Pa_BtnL_00");
        mBtnR00 = screen->sub_7100A480B4("Pa_SystemWindow_00/Pa_BtnR_00");
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

// 0x71009c81cc
// NON_MATCHING: the original stores 0x1ac / 0x1b4 before the memset of 0x130 and orders the later stores differently.
Unk_710247e0c8::Unk_710247e0c8(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

Unk_710247e0c8::~Unk_710247e0c8() = default;

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

// NON_MATCHING: placeholder destructor; the original (0x71009cc7c4) also destroys members or bases
// this class does not declare yet.
Unk_710247e990::~Unk_710247e990() = default;

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
