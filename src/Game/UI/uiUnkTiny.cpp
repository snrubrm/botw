#include "Game/UI/uiUnkTiny.h"
#include "KingSystem/Sound/sndMgr.h"
#include <math/seadMathCalcCommon.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiUtils.h"
#include <nn/ui2d/Pane.h>

// The "{ ; }" destructors keep the original's vtable store (upstream GameDataFlagSelector::~GameDataFlagSelector() { ; },
// commit 96101229; the original D1 is `str vptr; ret`).
namespace uking::ui {

// 0x7100934a6c
UiStringEntry::UiStringEntry() {}

Unk_7102474b38::Unk_7102474b38() = default;

void Unk_7102474b38::sub_7100932F74(eui::LayoutEx* first, eui::LayoutEx* second) {
    mFirst = first;
    mSecond = second;
}

eui::LayoutEx* Unk_7102474b38::sub_7100932F7C(s32 index) const {
    switch (index) {
    case 0:
        return mFirst;
    case 1:
        return mSecond;
    default:
        return nullptr;
    }
}

void Unk_7102474b38::sub_7100932FA8(s32 index, eui::LayoutEx* layout, bool flag) {
    sub_7100AA1D5C(sub_7100932F7C(index), layout, flag);
}

void Unk_7102474b38::sub_7100932FDC(s32 index, bool animated) {
    auto* layout = sub_7100932F7C(index);
    if (!layout)
        return;
    if (animated) {
        if (layout->_91 == 1 || layout->_91 == 2)
            layout->startAnimCloseImpl_(false, false);
    } else if (layout->_91 != 0) {
        layout->startAnimCloseImpl_(false, true);
    }
}

bool Unk_7102474b38::sub_7100933038(s32 index) const {
    auto* layout = sub_7100932F7C(index);
    return layout && (layout->_91 == 1 || layout->_91 == 2);
}

void Unk_7102474b38::sub_710093307C(s32 index, nn::ui2d::Pane* parent) {
    auto* layout = sub_7100932F7C(index);
    if (!layout)
        return;
    if (layout->GetPane()->GetParent())
        layout->GetPane()->GetParent()->RemoveChild(layout->GetPane());
    parent->AppendChild(layout->GetPane());
}

void Unk_7102474b38::sub_71009330E4() {
    sub_7100932FDC(0, false);
    sub_7100932FDC(1, false);
}

// 0x7100932f6c
Unk_7102474b38::~Unk_7102474b38() = default;

// 0x71009332f0
Unk_7102474b78::Unk_7102474b78() = default;

// 0x71009333a4
void Unk_7102474b78::set30(eui::Animator* animator) {
    _30 = animator;
}

// 0x71009333c4
void Unk_7102474b78::set38(s32 value) {
    _38 = value;
}

// 0x7100933314
Unk_7102474b78::~Unk_7102474b78() = default;

// 0x71009336a4
Unk_7102474ba8::Unk_7102474ba8() = default;

Unk_7102474ba8::~Unk_7102474ba8() = default;

void Unk_7102474ba8::sub_710093372C(bool first) {
    if (!_8)
        return;
    if (first) {
        if (_8->_91 == 3 || _8->_91 == 0)
            _8->sub_7100BDDE7C(false, 0, true);
    } else if (_8->_91 != 2) {
        _8->sub_7100BDDE7C(false, 1, true);
    }
}

void Unk_7102474ba8::sub_7100933774(bool first) {
    if (!_8)
        return;
    if (first) {
        if (_8->_91 == 1 || _8->_91 == 2)
            _8->startAnimCloseImpl_(false, false);
    } else if (_8->_91 != 0) {
        _8->startAnimCloseImpl_(false, true);
    }
}

bool Unk_7102474ba8::sub_71009337B0() const {
    return _8 && (_8->_91 == 1 || _8->_91 == 2);
}

void Unk_7102474ba8::sub_71009337D4(nn::ui2d::Pane* parent) {
    if (!_8)
        return;
    if (auto* old_parent = _8->mPane->GetParent())
        old_parent->RemoveChild(_8->mPane);
    parent->AppendChild(_8->mPane);
}

// NON_MATCHING: the compiler uses separate false-return blocks.
bool Unk_7102474ba8::sub_7100933828(const nn::ui2d::Pane* parent) const {
    return parent && _8 && _8->mPane->GetParent() == parent;
}

void Unk_7102474ba8::sub_7100933850(bool reverse, bool animated) {
    if (!_10)
        return;
    if (reverse) {
        if (animated)
            _10->PlayAuto(-1.0f);
        else
            _10->StopAtMin();
    } else {
        if (animated)
            _10->PlayAuto(1.0f);
        else
            _10->StopAtMax();
    }
}

// 0x7100934b8c
// 0x7100934aec
Unk_7102474be8::Unk_7102474be8() {}

Unk_7102474be8::~Unk_7102474be8() = default;

Unk_7102474c28::Unk_7102474c28() = default;

void Unk_7102474c28::sub_7100936998(eui::LayoutEx* layout) {
    if (!layout)
        return;
    mLayout = layout;
    mPageAnimator = layout->createAnimatorAuto("PageNum", false);
    if (mPageAnimator)
        mPageStep = f32(mPageAnimator->GetFrameSize()) / 20.0f;
    mScrollAnimator = layout->createAnimatorAuto("Scroll", false);
    if (mScrollAnimator)
        mScrollStep = f32(mScrollAnimator->GetFrameSize()) / 20.0f;
}

void Unk_7102474c28::sub_7100936A28(s32 value) {
    if (mPageAnimator) {
        value = sead::Mathi::clamp(value, 0, 20);
        mPageAnimator->Stop(value * mPageStep);
        mPageValue = value;
    }
}

// NON_MATCHING: the natural integer increment and virtual stop target/clamp scheduling differ.
void Unk_7102474c28::sub_7100936A7C(s32 value) {
    if (mScrollAnimator) {
        if (mPageValue >= 1)
            ++value;
        mScrollAnimator->Stop(sead::Mathi::clamp(value, 0, 20) * mScrollStep);
    }
}

void Unk_7102474c28::sub_7100936AD8() {
    if (mScrollAnimator)
        mScrollAnimator->StopAtMin();
}

// 0x7100936990
Unk_7102474c28::~Unk_7102474c28() = default;

void Unk_7102474c48::sub_7100936B18(eui::LayoutEx* layout) {
    if (layout) {
        mLayout = layout;
        mAnimator = layout->tryCreateAnimatorAuto("GuideState", false);
        if (mAnimator) {
            mActive = true;
            mAnimator->Stop(0.0f);
        }
    }
}

// NON_MATCHING: the four guide frames lower to a different Boolean selection tree.
void Unk_7102474c48::sub_7100936B7C(bool first, bool second) {
    if (mAnimator) {
        mActive = first || second;
        const f32 frame = first ? (second ? 0.0f : 2.0f) : (second ? 1.0f : 3.0f);
        mAnimator->Stop(frame);
    }
}

// 0x7100936b10
Unk_7102474c48::~Unk_7102474c48() = default;

// 0x7100947b7c
Unk_7102475158::~Unk_7102475158() = default;

// 0x7100949ce0

// 0x710095023c
Unk_7102475368::~Unk_7102475368() = default;

// 0x710096a890
Unk_7102475388::~Unk_7102475388() = default;

// 0x710095b124
Unk_71024753a8::~Unk_71024753a8() = default;

// 0x710095a3e4
Unk_7102476a80::~Unk_7102476a80() = default;

// 0x710096a89c
Unk_7102476b20::~Unk_7102476b20() = default;

// 0x7100968038
Unk_7102476b40::~Unk_7102476b40() = default;

// 0x7100968034
Unk_7102476b60::~Unk_7102476b60() = default;

// 0x7100987fb4
Unk_7102477468::Unk_7102477468() = default;

void Unk_7102477468::sub_7100987FBC(eui::UniteButton* button) {
    if (button) {
        mButton = button;
        button->setFlag10(false);
        mIconAnimator = mButton->mLayout->createAnimatorAuto("Icon", false);
    }
}

void Unk_7102477468::sub_7100988010(u32 frame) {
    if (mIconAnimator)
        mIconAnimator->Stop(frame);
}

void Unk_7102477468::sub_710098802C(bool checked) {
    if (mButton)
        mButton->ForceSetChecked(checked);
}

bool Unk_7102477468::sub_7100988040() const {
    return mButton && mButton->mChecked;
}

void Unk_7102477468::sub_7100988060(bool play) {
    if (mButton)
        mButton->PlayDisableAnim(play);
}

bool Unk_7102477468::sub_710098807C() const {
    return mButton && mButton->IsPlayDisableAnim();
}

Unk_7102477468::~Unk_7102477468() = default;

// 0x71009880a4
Unk_7102477488::Unk_7102477488() = default;

void Unk_7102477488::sub_71009880AC(eui::UniteButton* button) {
    if (button) {
        mButton = button;
        mPatternAnimator = button->mLayout->createAnimatorAuto("Pattern", false);
    }
}

void Unk_7102477488::sub_71009880E8(u32 frame) {
    if (mPatternAnimator)
        mPatternAnimator->Stop(frame);
}

eui::UniteButton* Unk_7102477488::sub_7100988104() const { return mButton; }

eui::LayoutEx* Unk_7102477488::sub_710098810C() const {
    return mButton ? mButton->mLayout : nullptr;
}

void Unk_7102477488::sub_7100988138(bool on) {
    if (mButton)
        mButton->setFlag10(on);
}

void Unk_7102477488::sub_7100988154(bool checked) {
    if (mButton)
        mButton->ForceSetChecked(checked);
}

Unk_7102477488::~Unk_7102477488() = default;

// 0x7100988ee8
Unk_71024774c8::Unk_71024774c8() = default;

void Unk_71024774c8::sub_7100988EF0(eui::LayoutEx* layout) {
    if (layout) {
        mLayout = layout;
        mTexturePatternAnimator = layout->createAnimatorAuto("TexPattern", false);
    }
}

// NON_MATCHING: the final Animator virtual call has different register allocation and scheduling.
void Unk_71024774c8::sub_7100988F30(f32 frame) {
    if (mTexturePatternAnimator) {
        if (frame < 0.0f) {
            sub_7100988FE8();
            return;
        }
        if (mLayout->_91 == 3 || mLayout->_91 == 0 || !mLayout->_70 || !mLayout->_70->mEnabled)
            mLayout->sub_7100BDDE7C(false, 1, true);
        mTexturePatternAnimator->Stop(frame);
    }
}

void Unk_71024774c8::sub_7100988FE8() {
    if (mLayout && (mLayout->_91 == 1 || mLayout->_91 == 2))
        mLayout->startAnimCloseImpl_(false, true);
}

Unk_71024774c8::~Unk_71024774c8() = default;

// 0x7100989a78
Unk_7102477508::Unk_7102477508() = default;

void Unk_7102477508::sub_7100989A80(eui::LayoutEx* layout) {
    if (layout) {
        mLayout = layout;
        mCategoryAnimator = layout->createAnimatorAuto("Category", false);
        mHeartMarkOffAnimator = mLayout->createAnimatorAuto("HeartMarkOff", true);
        mNumberAnimator = mLayout->createAnimatorAuto("Number", true);
    }
}

// NON_MATCHING: the heart-mark branch canonicalizes value > 0 to a compare against 1.
void Unk_7102477508::sub_7100989AF0(s32 category, s32 value, s32 number) {
    if (mLayout) {
        if (category == -1) {
            mLayout->startAnimCloseImpl_(false, true);
            return;
        }
        mLayout->sub_7100BDDE7C(false, 1, true);
        if (mCategoryAnimator)
            mCategoryAnimator->Stop(category);
    }
    if (u32(category) <= 3) {
        sub_7100989C0C(value);
        if (mNumberAnimator) {
            if (number <= 1) {
                mNumberAnimator->StopAtMin();
            } else {
                f32 frame;
                switch (number) {
                case 2: frame = 1.0f; break;
                case 3: frame = 2.0f; break;
                case 5: frame = 3.0f; break;
                default: frame = 0.0f; break;
                }
                mNumberAnimator->Stop(frame);
            }
        }
    } else if (category == 4 || category == 5) {
        if (mHeartMarkOffAnimator) {
            if (value > 0)
                mHeartMarkOffAnimator->StopAtMin();
            else
                mHeartMarkOffAnimator->StopAtMax();
        }
    }
}

void Unk_7102477508::sub_7100989C0C(s32 value) {
    if (mLayout) {
        sead::FixedSafeString<32> text;
        text.format("%d", value);
        sead::FixedSafeString<32> special;
        if (formatSpecialAttackPower(value, &special))
            text = special;
        setWidgetString(mLayout, "T_Num_00", text);
    }
}

Unk_7102477508::~Unk_7102477508() = default;

// 0x71009a4d24
Unk_7102479bb0::~Unk_7102479bb0() = default;

// 0x71009a7fa0
Unk_7102479f90::~Unk_7102479f90() = default;

// 0x71009a8be4
Unk_7102479fb0::~Unk_7102479fb0() = default;

// 0x71009b14f0
Unk_710247aa30::Unk_710247aa30() = default;

void Unk_710247aa30::sub_71009B14F8(eui::LayoutEx* layout) {
    if (layout) {
        mLayout = layout;
        mBreakLoopAnimator = layout->createAnimatorAuto("BreakLoop", true);
        if (mBreakLoopAnimator)
            mBreakLoopAnimator->StopAtMin();
        mNewAnimator = mLayout->createAnimatorAuto("New", true);
        if (mNewAnimator)
            mNewAnimator->StopAtMin();
    }
}

// NON_MATCHING: the compiler shares the New Animator frame load across both state branches.
void Unk_710247aa30::sub_71009B1578(s32 state) {
    if (mNewAnimator) {
        if (state != 0) {
            if (mNewAnimator->mFrame != 0.0f)
                mNewAnimator->StopAtMin();
        } else if (mNewAnimator->mFrame != mNewAnimator->GetFrameSize()) {
            mNewAnimator->StopAtMax();
        }
    }
    if (mBreakLoopAnimator) {
        if (state == 2)
            mBreakLoopAnimator->PlayAuto(1.0f);
        else if (mBreakLoopAnimator->mRate != 0.0f)
            mBreakLoopAnimator->StopAtMin();
    }
}

// NON_MATCHING: shared frame load and the common StopAtMin exit use different scheduling.
void Unk_710247aa30::sub_71009B163C(s32 state, f32 frame) {
    if (state == 2) {
        if (mBreakLoopAnimator)
            mBreakLoopAnimator->PlayFromFrame(eui::Animator::PlayType(1), frame, 1.0f);
        if (mNewAnimator && mNewAnimator->mFrame != 0.0f)
            mNewAnimator->StopAtMin();
    } else {
        if (mNewAnimator) {
            if (state != 0) {
                if (mNewAnimator->mFrame != 0.0f)
                    mNewAnimator->StopAtMin();
            } else if (mNewAnimator->mFrame != mNewAnimator->GetFrameSize()) {
                mNewAnimator->StopAtMax();
            }
        }
        if (mBreakLoopAnimator && mBreakLoopAnimator->mRate != 0.0f)
            mBreakLoopAnimator->StopAtMin();
    }
}

nn::ui2d::Pane* Unk_710247aa30::sub_71009B170C() const {
    return mLayout ? mLayout->GetPane()->FindPaneByName("N_Chemical_00", true) : nullptr;
}

nn::ui2d::Material* Unk_710247aa30::sub_71009B1738() const {
    if (mLayout) {
        if (auto* pane = mLayout->GetPane()->FindPaneByName("P_Icon_00", true))
            return pane->GetMaterial(0);
    }
    return nullptr;
}

f32 Unk_710247aa30::sub_71009B1784() const {
    return mBreakLoopAnimator && mBreakLoopAnimator->mRate != 0.0f ? mBreakLoopAnimator->mFrame : 0.0f;
}

Unk_710247aa30::~Unk_710247aa30() = default;

// 0x71009b2054
Unk_710247adc8::Unk_710247adc8() = default;

void Unk_710247adc8::sub_71009B205C(eui::LayoutEx* layout) {
    if (!layout)
        return;
    mLayout = layout;
    mTexturePatternAnimator = layout->createAnimatorAuto("TexPattern", false);
    mColorAnimator = mLayout->createAnimatorAuto("Color", false);
    mNumberAnimator = mLayout->createAnimatorAuto("Number", false);
    mOldNumberAnimator = mLayout->createAnimatorAuto("NumberOld", false);
}

void Unk_710247adc8::sub_71009B21B4(s32 value, bool old) {
    sead::FixedSafeString<32> text;
    text.format("%d", value);
    sead::FixedSafeString<32> special;
    if (formatSpecialAttackPower(value, &special))
        text = special;
    if (old)
        setWidgetString(mLayout, "T_OldNum_00", text);
    else
        setWidgetString(mLayout, "T_Num_00", text);
}

void Unk_710247adc8::sub_71009B20E4(u32 category, s32 value, s32 old_number) {
    if (!mLayout)
        return;
    if (mTexturePatternAnimator)
        mTexturePatternAnimator->Stop(category);
    if (mColorAnimator)
        mColorAnimator->StopAtMin();
    sub_71009B21B4(value, true);
    if (!mOldNumberAnimator)
        return;
    if (old_number <= 1) {
        mOldNumberAnimator->StopAtMin();
    } else {
        f32 frame;
        switch (old_number) {
        case 2: frame = 1.0f; break;
        case 3: frame = 2.0f; break;
        case 4: frame = 0.0f; break;
        case 5: frame = 3.0f; break;
        default: frame = 0.0f; break;
        }
        mOldNumberAnimator->Stop(frame);
    }
}

Unk_710247adc8::~Unk_710247adc8() = default;

// 0x71009b2ee0
Unk_710247ae08::~Unk_710247ae08() = default;

// 0x71009b2ee8
Unk_710247ae28::~Unk_710247ae28() = default;

// 0x71009c5098
Unk_710247d8d8::~Unk_710247d8d8() = default;

// 0x71009c66e4
Unk_710247dc50::~Unk_710247dc50() = default;

// 0x71009c6870
Unk_710247dc70::~Unk_710247dc70() = default;

// 0x71009dff74
Unk_71024810d8::~Unk_71024810d8() = default;

// 0x71009e7e00
Unk_71024810f8::~Unk_71024810f8() = default;

// 0x71009dff7c
Unk_7102481118::~Unk_7102481118() = default;

// 0x71009ec6c8
Unk_7102481e50::~Unk_7102481e50() = default;

// 0x7100a6cb6c
Unk_710249c3b0::~Unk_710249c3b0() = default;

// 0x7100a6cbb8
Unk_710249c3d0::~Unk_710249c3d0() = default;

// 0x7100a6cc44
Unk_710249c3f0::~Unk_710249c3f0() = default;

// 0x7100a6d2c8
Unk_710249c410::~Unk_710249c410() = default;

// 0x71009ec6c8
Unk_7102516880::~Unk_7102516880() = default;

// 0x7100933140
Unk_7102474b58::Unk_7102474b58(void* owner) : _8(owner) {}

// 0x7100933184
Unk_7102474b58::~Unk_7102474b58() { ; }

// 0x710093319c
void Unk_7102474b58::sub_71009319C(Index index, const sead::SafeString& a, const sead::SafeString& b) {
    Entry& entry = _10[index];
    entry.a = a;
    entry.b = b;
}

// 0x71009333ac
void Unk_7102474b78::sub_71009333AC() {
    if (_20)
        _20->StopAtMin();
}

// 0x7100959a84
Unk_7102476a40::~Unk_7102476a40() { ; }

// 0x7100959cfc
Unk_7102476a60::~Unk_7102476a60() { ; }

// 0x7100968020
Unk_7102476b00::~Unk_7102476b00() { ; }

Unk_71024774a8::Unk_71024774a8()
    : mLayout(nullptr), mAnimators{}, _58(0.0f), _5c(0), _60(sead::SafeString::cEmptyString) {
    mAnimators.fill(nullptr);
}

// 0x71009884a8
void Unk_71024774a8::sub_71009884A8(eui::LayoutEx* layout) {
    mLayout = layout;
    sub_71009884B0();
}

void Unk_71024774a8::sub_7100988AF4(bool open) {
    if (open)
        mLayout->sub_7100BDDE7C(false, 1, true);
    else
        mLayout->startAnimCloseImpl_(false, true);
}

f32 Unk_71024774a8::sub_7100988D00(s32 index) const { return mAnimators[index]->mFrame; }

bool Unk_71024774a8::sub_7100988D1C(s32 index) const {
    const auto* animator = mAnimators[index];
    return animator->mFrame == animator->GetFrameSize();
}

bool Unk_71024774a8::sub_7100988D60(s32 index) const {
    return mAnimators[index]->mFrame == 0.0f;
}

void Unk_71024774a8::sub_7100988D84(s32 index, f32 frame) {
    mAnimators[index]->mFrame = frame;
}

void Unk_71024774a8::sub_7100988DA0(s32 index, f32 speed) {
    mAnimators[index]->PlayFromCurrent(eui::Animator::PlayType(0), speed);
}

void Unk_71024774a8::sub_7100988DC4() { _58 = 100.0f; }

// NON_MATCHING: the pane pointer load is scheduled before the input vector loads.
void Unk_71024774a8::sub_7100988DD0(const sead::Vector2f& position) {
    mLayout->GetPane()->SetPosition({position.x, position.y, 0.0f});
}

Unk_71024774a8::~Unk_71024774a8() { ; }

// 0x71009dfd4c
Unk_71024810b8::~Unk_71024810b8() { ; }

// NON_MATCHING: the original stores `_8` (the base class member) right after loading the vtable address, ours
// schedules it after the 64-bit constant of `_10`
// 0x7100a82fbc
Unk_710249d300::Unk_710249d300() = default;

// 0x7100a8331c
Unk_710249d300::~Unk_710249d300() { ; }

// 0x7100937eec
Unk_7102474df8::Unk_7102474df8() = default;

// NON_MATCHING: the original keeps the Vector2f::zero pair in FP registers across the switch (ldp/stp s2, s1,
// fneg) and loads it before the switch; we sink the load into the default path and materialize the pair in
// integer registers (stp w8, w9, eor). Everything after the store matches.
// 0x7100938408
void Unk_7102474df8::sub_7100938408(Unk_7102474dd0* entry) {
    if (entry == nullptr)
        return;

    if (_10.size() != 0)
        _28 += _38;
    const f32 offset = _28;

    sead::Vector2f dir = sead::Vector2f::zero;
    switch (_34) {
    case 0:
        dir.set(0.0f, offset);
        break;
    case 1:
        dir.set(0.0f, -offset);
        break;
    case 2:
        dir.set(-offset, 0.0f);
        break;
    case 3:
        dir.set(offset, 0.0f);
        break;
    }
    entry->_18 = dir;
    entry->_8 = this;
    // the original ignores a full list (pushBack's result is discarded)
    _10.pushBack(entry);
}

// 0x7100937f5c
Unk_7102474df8::~Unk_7102474df8() {
    _10.freeBuffer();
}

// 0x71009338a0
Unk_7102474bc8::Unk_7102474bc8() {}

// 0x7100933e50
bool Unk_7102474bc8::sub_7100933E50() const {
    for (s32 i = 0; i < _8; i++) {
        UiSlotTarget* target = _130[i].target;
        if (!target || target->_104 != 0)
            return false;
    }
    return true;
}

// 0x7100933fb8
void Unk_7102474bc8::sub_7100933FB8(u32 index, UiSlotTarget* target) {
    if (index < _8)
        _130[index].target = target;
}

// 0x7100933938
// 0x7100934308
void Unk_7102474bc8::sub_7100934308(s32 id, const sead::SafeString& text, s32 value) {
    UiStringEntry entry;
    entry._0 = id;
    entry._8.copy(text);
    entry._120 = value;
    sub_7100933FE0(entry);
}

Unk_7102474bc8::~Unk_7102474bc8() {
    _130.freeBuffer();
    _140.freeBuffer();
}

// 0x7100937d9c
Unk_7102474dd0::~Unk_7102474dd0() = default;

// 0x7100937e9c
void Unk_7102474dd0::m2(const sead::Vector2f& a, const sead::Vector2f& b) {
    _20 = _18;
    const sead::Vector2f pos = a + b + _20;
    _20 = pos;
    if (Unk_PaneTransform* pane = _10) {
        pane->_30.x = pos.x;
        pane->_30.y = pos.y;
        pane->_38 = 0;
        pane->_58 |= 0x10;
    }
}

// 0x71010a7bcc
Unk_7102509148::Unk_7102509148() = default;

// 0x71010a7bf8
Unk_7102509148::~Unk_7102509148() = default;

// Unk_7102475368 accessors (placeholder names after the offsets)
// 0x7100950244
u8* Unk_7102475368::get10() {
    return _10;
}

// 0x710095024c
void Unk_7102475368::set18(const Pair& value) {
    _18.a = value.a;
    _18.b = value.b;
}

// 0x7100950260
Unk_7102475368::Pair* Unk_7102475368::get18() {
    return &_18;
}

// 0x7100950268
void Unk_7102475368::set20(const Pair& value) {
    _20.a = value.a;
    _20.b = value.b;
}

// 0x710095027c
Unk_7102475368::Pair* Unk_7102475368::get20() {
    return &_20;
}

// 0x7100950284
void Unk_7102475368::set28(f32 value) {
    _28 = value;
}

// 0x710095028c
f32 Unk_7102475368::get28() const {
    return _28;
}

// 0x7100950294
void Unk_7102475368::set2c(f32 value) {
    _2c = value;
}

// 0x710095029c
f32 Unk_7102475368::get2c() const {
    return _2c;
}

// 0x71009502a4
u8* Unk_7102475368::get30() {
    return _30;
}

// 0x71009502ac
void Unk_7102475368::set38(f32 value) {
    _38 = value;
}

// 0x71009502b4
f32 Unk_7102475368::get38() const {
    return _38;
}

// 0x71009502bc
void Unk_7102475368::set3c(f32 value) {
    _3c = value;
}

// 0x71009502c4
f32 Unk_7102475368::get3c() const {
    return _3c;
}

// 0x71009502cc
void Unk_7102475368::set40(const Pair& value) {
    _40.a = value.a;
    _40.b = value.b;
}

// 0x71009502e0
Unk_7102475368::Pair* Unk_7102475368::get40() {
    return &_40;
}

// 0x71009502e8
s32 Unk_7102475368::get48() const {
    return _48;
}

// 0x71009502f0
u8* Unk_7102475368::get60() {
    return _60;
}

// Unk_7102474be8 methods (placeholder names after the offsets)
// 0x7100935930
// NON_MATCHING: stack slot placement for the sound mode.
void Unk_7102474be8::sub_71009359E8() {
    const s32 mode = _95f;
    if (_964) {
        ksys::snd::SoundMgr::instance()->mUiSoundMgr->sub_710105D844(&mode);
        _964 = 0;
    }
}

void Unk_7102474be8::set940(s32 value) {
    _940 = value;
}

// 0x71009358c4
void Unk_7102474be8::set944(f32 value) {
    _944 = value;
}

// 0x7100935894
void Unk_7102474be8::set948(f32 value) {
    if (value >= 0.0f && value <= 100.0f)
        _948 = value;
}

// 0x71009358b4
void Unk_7102474be8::set958(f32 value) {
    if (value >= 0.0f)
        _958 = value;
}

// 0x7100935938
void Unk_7102474be8::playAnimator918() {
    _918->PlayAuto(1.0f);
}

// 0x710093594c
void Unk_7102474be8::stopAnimator918() {
    _918->StopAtMax();
}

// 0x710093595c
void Unk_7102474be8::playAnimator8e0() {
    _8e0->PlayAuto(1.0f);
}

// 0x7100935970
void Unk_7102474be8::stopAnimator8e0() {
    _8e0->StopAtMax();
}

// 0x7100935980
bool Unk_7102474be8::isAnimator8e0Playing() const {
    return _8e0->mRate != 0;
}

// 0x7100935994
f32 Unk_7102474be8::getAnimator8e0Frame() const {
    return _8e0->mFrame;
}

// 0x71009359a0
void Unk_7102474be8::playAnimator8e0FromFrame(f32 frame) {
    _8e0->PlayFromFrame(eui::Animator::PlayType(0), frame, 1.0f);
}

// 0x71009359b0
void Unk_7102474be8::playAnimator910() {
    _910->PlayAuto(1.0f);
}

// 0x71009359c4
bool Unk_7102474be8::isAnimator910Playing() const {
    return _910->mRate != 0;
}

// 0x71009359d8
void Unk_7102474be8::stopAnimator910(f32 frame) {
    _910->Stop(frame);
}

}  // namespace uking::ui
