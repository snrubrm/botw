#include "Game/UI/uiScreenChildStates.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiCapturePane.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiLetterAnimControl.h"
#include "Game/UI/euiMessageString.h"
#include "KingSystem/Quest/qstQuest.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameSaveSystem.h"
#include "Game/gameStageBinder.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/World/worldManager.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ui {

// 0x7100985eb4
Unk_7102476db8::Unk_7102476db8(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x7100986068
void Unk_7102476db8::m24() {
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

// 0x7100986240
// NON_MATCHING: the compiler combines the odd state tests into one bitset.
void Unk_7102476db8::m25() {
    if (_104 == 7 || _104 == 1 || _104 == 3 || _104 == 5)
        sub_7100986268();
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

// 0x710098c278
Unk_7102477c30::Unk_7102477c30(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x710098c688 / 0x710098c68c: the native table overrides only these two update hooks.
void Unk_7102477c30::m24() {}
void Unk_7102477c30::m25() {}


// 0x71009bc9bc
Unk_710247bcb8::Unk_710247bcb8(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x71009bcbdc
void Unk_710247bcb8::m24() {
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

// 0x71009bcff8: MainScreen 0x7100a1adc4 resets the status child before the next update.
void Unk_710247bcb8::sub_71009BCFF8() {
    _188 = -1;
    _18c = 0;
    _190 = -1;
    m78();
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

// 0x71009b9b38
Unk_710247b428::Unk_710247b428(eui::LayoutEx* layout)
    : ScreenChildEx(layout), _130{}, _1a8(nullptr), _1b0{} {}


Unk_710247ae48::~Unk_710247ae48() = default;

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
    mStateMachine.changeState(&sUnk_71025d98a0);
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
        mStateMachine.changeState(&sUnk_71025d9ec0);
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
    mStateMachine.changeState(&sUnk_71025d9e00);
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
        mStateMachine.changeState(&sUnk_71025da040);
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
        mStateMachine.changeState(&sUnk_71025da100);
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
        mStateMachine.changeState(&sUnk_71025d9e00);
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
        mStateMachine.changeState(&sUnk_71025d9e00);
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
        mStateMachine.changeState(&sUnk_71025da220);
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
        mStateMachine.changeState(&sUnk_71025d9e00);
        return;
    }
    if (!sub_7100A64304())
        createTitleStageBinder(true, true);
}

// 0x71009bc054
void Unk_710247b428::m151() {}

// 0x71009bc0b4
s32 Unk_710247b428::m152() { return 0; }

// 0x71009c9878
void Unk_710247e468::m24() {
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
    mStateMachine.run();
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
    mStateMachine.changeState(&sUnk_71025dbb28);
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
        mStateMachine.changeState(&sUnk_71025dbb88);
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
// NON_MATCHING: return block placement and branch polarity.
void Unk_710247e468::m110() {
    if (_138 && _138->mRate == 0.0f) {
        sub_71009C9D5C(false);
        mStateMachine.changeState(&sUnk_71025dbb28);
    }
}

// 0x71009ca340
void Unk_710247e468::m111() {
    _138->Play(eui::Animator::PlayType(0), -1.0f);
}

// 0x71009ca35c
s32 Unk_710247e468::m108() { return 0; }

// 0x71009ca364
s32 Unk_710247e468::m112() { return 0; }

}  // namespace uking::ui
