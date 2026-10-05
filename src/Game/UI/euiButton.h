#pragma once

#include <basis/seadTypes.h>
#include "Game/UI/euiControlBase.h"
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace nn::ui2d {
class ControlSrc;
class Pane;
}  // namespace nn::ui2d

namespace eui {

class ButtonGroup;
class LayoutEx;

// Base class of the eui buttons. The vtable has 31 slots (ControlBase's 5 + 26 own ones; AnimButton adds 10 more).
// Button requests (On / Off / Down / Cancel) are queued in `mQueue` (at most 4 entries) and processed by Update().
// Names of the hooks are guesses from the CSV names of the AnimButton overrides (Process* / Start* / Finish*) and
// the ButtonBase::State enum of the original (its enumerators are not known).
class ButtonBase : public ControlBase {
public:
    // Guessed names; ForceOff / ForceOn / ForceDown set the states 0 / 3 / 5.
    enum State {
        kOff = 0,
        kStartOn = 1,
        kStartOff = 2,
        kOn = 3,
        kStartDown = 4,
        kDown = 5,
        kCancel = 6,
    };

    // The request kinds stored in the queue.
    enum Request : u8 {
        kRequestOn = 0,
        kRequestOff = 1,
        kRequestDown = 2,
        kRequestCancel = 3,
    };

    ButtonBase();

    const char* getClassName() const override { return "ButtonBase"; }
    NN_RUNTIME_TYPEINFO(ControlBase)

    void Update(f32 dt) override;

    // Slots 5-8 (0x7100bd71b4 / 0x7100bd7240 / 0x7100bd72cc / 0x7100bd7360; the name `Down` is known from the CSV's
    // HoverButton::Down): queue a request (if the button's flags allow it) and make sure the button is linked into its
    // group's update list.
    virtual void On();
    virtual void Off();
    virtual void Down();
    virtual void Cancel();

    virtual void ForceOff();
    virtual void ForceOn();
    virtual void ForceDown();
    // 0x7100bd77f0 (slot 12)
    virtual void setFlag10(bool on);

    // Slots 13-16: process the front request; true if it was handled.
    virtual bool ProcessOn();
    virtual bool ProcessOff();
    virtual bool ProcessDown();
    virtual bool ProcessCancel();

    // Slots 17-20 / 21-24 / 25-28
    virtual bool UpdateOn();
    virtual bool UpdateOff();
    virtual bool UpdateDown();
    virtual bool UpdateCancel();
    virtual void StartOn();
    virtual void StartOff();
    virtual void StartDown();
    virtual void StartCancel();
    virtual void FinishOn();
    virtual void FinishOff();
    virtual void FinishDown();
    virtual void FinishCancel();

    // Slot 29: store the new state (AnimButton also notifies the screen), slot 30: store it silently.
    virtual void changeState(State state);
    virtual void setState(State state);

    // 0x7100bd7a6c
    bool IsDowning() const;

    /* 0x28 */ ListNode mNode;  // linked into ButtonGroup::mList while requests are pending
    /* 0x38 */ u8 mState = kOff;
    /* 0x39 */ u8 _39 = 0;
    /* 0x3a */ u16 mFlags = 0x1f;
    /* 0x3c */ u8 mQueue[4];
    /* 0x40 */ s32 mQueueCount = 0;
    /* 0x44 */ s32 mTag = 0;

protected:
    // inline-only in the original; names are guesses. Evidence: the "append request unless it is queued, then link the
    // button into its group's list" sequence is repeated in the four request functions, the "pop the front request"
    // loop in Update (five times).
    void pushRequest(Request request);
    void linkToGroup();
    void popRequest();
    void processRequests();
};
static_assert(sizeof(ButtonBase) == 0x48);

// A screen's buttons (CSV eui::ButtonGroup; vtable 0x24c7008). `mButtons` links the ControlBase::_8 nodes of its
// buttons, `mPending` the ButtonBase::mNode of the buttons with queued requests.
class ButtonGroup {
public:
    ButtonGroup();
    virtual ~ButtonGroup() = default;
    virtual void m2();

    // 0x7100bd8378
    bool IsExistExcludingDown() const;
    // 0x7100bd83d8 (CSV unnamed; called by Screen::doOpenStart; not decompiled)
    void sub_7100BD83D8();
    // 0x7100bd817c / 0x7100bd8338 / 0x7100bd8118
    ButtonBase* FindDownButton();
    ButtonBase* FindButtonByTag(s32 tag);
    void SetTouchDevice(bool touch);

    /* 0x08 */ ListNode mButtons;
    /* 0x18 */ ListNode mPending;
    /* 0x28 */ void* _28 = nullptr;
    /* 0x30 */ void* _30 = nullptr;
    /* 0x38 */ u32 _38 = 3;
};
static_assert(sizeof(ButtonGroup) == 0x40);

class AnimatorSet;
class Animator;

// A button whose states are driven by an AnimatorSet (CSV eui::AnimButton; 0x68 bytes, vtable 0x24c6da8 with 41 slots).
class AnimButton : public ButtonBase {
public:
    AnimButton();

    const char* getClassName() const override { return "AnimButton"; }
    NN_RUNTIME_TYPEINFO(ButtonBase)

    void Down() override;
    void ForceOff() override;
    void ForceOn() override;
    void ForceDown() override;
    bool ProcessOn() override;
    bool ProcessOff() override;
    bool ProcessCancel() override;
    bool UpdateOn() override;
    bool UpdateOff() override;
    bool UpdateDown() override;
    void StartOn() override;
    void StartOff() override;
    void StartDown() override;
    void FinishDown() override;
    void changeState(State state) override;
    void setState(State state) override;

    // Slots 31-40 (names are guesses except for the CSV ones)
    virtual void Build(const nn::ui2d::ControlSrc& src, LayoutEx* layout);
    virtual bool HitTest(const sead::Vector2f& pos) const;
    virtual void StartDrag(const sead::Vector2f& pos) {}
    virtual void UpdateDrag(const sead::Vector2f* pos) {}
    virtual void FinishDrag(const sead::Vector2f* pos) {}
    virtual void PlayDisableAnim(bool play);
    virtual void StopDisableAnim(bool atEnd);
    virtual void ActivateByBoxCursor();
    virtual void InactivateByBoxCursor();
    virtual void BuildStateAnim(const nn::ui2d::ControlSrc& src, LayoutEx* layout);

    // 0x7100bd65c0
    void SetTouch(bool touch);
    // 0x7100bd66ac
    bool DownOff(bool b);
    // 0x7100bd68f0
    bool IsPlayDisableAnim() const;
    // 0x7100bd6f08
    void CloneImpl_(const AnimButton& other, LayoutEx* layout, sead::Heap* heap);

    // 0x7100bd6a10 (called by the DragButton / UniteButton overrides and others; inlined by the AnimButton functions
    // above): selects the animator of the touch variant (`idx + 1`) if there is one.
    Animator* selectStateAnim(u32 idx);

    /* 0x48 */ AnimatorSet* mAnimators = nullptr;
    /* 0x50 */ Animator* mDisableAnim = nullptr;
    /* 0x58 */ nn::ui2d::Pane* mHitPane = nullptr;
    /* 0x60 */ nn::ui2d::Pane* mBoxCursorPane = nullptr;
};
static_assert(sizeof(AnimButton) == 0x68);

// A button with a checked state (CSV eui::CheckButton; 0x78 bytes, vtable 0x24c7030). Toggles on every press.
class CheckButton : public AnimButton {
public:
    NN_RUNTIME_TYPEINFO(AnimButton)
    const char* getClassName() const override { return "CheckButton"; }

    // inline-only in the original (TwoTouchCheckKeepButton's ctor inlines it)
    CheckButton() : mChecked(false), mToggleable(true), mCheckAnim(nullptr) {}
    CheckButton(const CheckButton& other, LayoutEx* layout, sead::Heap* heap);

    void Build(const nn::ui2d::ControlSrc& src, LayoutEx* layout) override;
    void StartDown() override;
    bool UpdateDown() override;

    /* 0x68 */ bool mChecked;
    /* 0x69 */ bool mToggleable;
    /* 0x70 */ Animator* mCheckAnim;
};
static_assert(sizeof(CheckButton) == 0x78);

// A check button that can only be checked by the user (CSV eui::CheckKeepButton; vtable 0x24c7188 with 42 slots).
class CheckKeepButton : public CheckButton {
public:
    NN_RUNTIME_TYPEINFO(CheckButton)
    const char* getClassName() const override { return "CheckKeepButton"; }

    CheckKeepButton() = default;
    CheckKeepButton(const CheckKeepButton& other, LayoutEx* layout, sead::Heap* heap);

    void StartDown() override;
    // Slot 41 (0x7100bd86a0): unchecks the button (the CSV names this UniteButton::Uncheck)
    virtual void Uncheck();
};
static_assert(sizeof(CheckKeepButton) == 0x78);

// vtable 0x24c7358
class DecisionButton : public AnimButton {
public:
    NN_RUNTIME_TYPEINFO(AnimButton)
    const char* getClassName() const override { return "DecisionButton"; }

    DecisionButton(const DecisionButton& other, LayoutEx* layout, sead::Heap* heap);

    bool ProcessOn() override;
    bool ProcessOff() override;
    void FinishDown() override;
};
static_assert(sizeof(DecisionButton) == 0x68);

// vtable 0x24c7640
class NormalButton : public AnimButton {
public:
    NN_RUNTIME_TYPEINFO(AnimButton)
    const char* getClassName() const override { return "NormalButton"; }

    NormalButton(const NormalButton& other, LayoutEx* layout, sead::Heap* heap);
};
static_assert(sizeof(NormalButton) == 0x68);

// A button with a cancel state (CSV eui::SelectButton; vtable 0x24c7798).
class SelectButton : public AnimButton {
public:
    NN_RUNTIME_TYPEINFO(AnimButton)
    const char* getClassName() const override { return "SelectButton"; }

    // inline-only in the original (DragButton's ctor inlines it)
    SelectButton() = default;
    SelectButton(const SelectButton& other, LayoutEx* layout, sead::Heap* heap);

    bool ProcessOn() override;
    bool ProcessOff() override;
    bool ProcessCancel() override;
    bool UpdateCancel() override;
    void StartCancel() override;
    void FinishDown() override;
    void FinishCancel() override;
    bool HitTest(const sead::Vector2f& pos) const override;
    void BuildStateAnim(const nn::ui2d::ControlSrc& src, LayoutEx* layout) override;
};
static_assert(sizeof(SelectButton) == 0x68);

// vtable 0x24c74b0. Moves the layout's root pane with the touch (drag).
class DragButton : public SelectButton {
public:
    NN_RUNTIME_TYPEINFO(SelectButton)
    const char* getClassName() const override { return "DragButton"; }

    DragButton();

    void StartCancel() override;
    void FinishCancel() override;
    void Build(const nn::ui2d::ControlSrc& src, LayoutEx* layout) override;
    void StartDrag(const sead::Vector2f& pos) override;
    void UpdateDrag(const sead::Vector2f* pos) override;
    void FinishDrag(const sead::Vector2f* pos) override;
    void BuildStateAnim(const nn::ui2d::ControlSrc& src, LayoutEx* layout) override;

    /* 0x68 */ nn::ui2d::Pane* mPane = nullptr;
    /* 0x70 */ sead::Vector2f mStartPos = {0, 0};
    /* 0x78 */ sead::Vector2f mPanePos = {0, 0};
    /* 0x80 */ bool mAllowX = true;
    /* 0x81 */ bool mAllowY = true;
};
static_assert(sizeof(DragButton) == 0x88);

// A checked-by-keeping button with a touch variant (CSV eui::TwoTouchCheckKeepButton; 0x90 bytes, vtable 0x24c7928).
class TwoTouchCheckKeepButton : public CheckKeepButton {
public:
    NN_RUNTIME_TYPEINFO(CheckKeepButton)
    const char* getClassName() const override { return "TwoTouchCheckKeepButton"; }

    TwoTouchCheckKeepButton();
    TwoTouchCheckKeepButton(const TwoTouchCheckKeepButton& other, LayoutEx* layout, sead::Heap* heap);

    bool HitTest(const sead::Vector2f& pos) const override;
    void ActivateByBoxCursor() override;
    void InactivateByBoxCursor() override;
    void BuildStateAnim(const nn::ui2d::ControlSrc& src, LayoutEx* layout) override;
    bool ProcessCancel() override;
    void StartDown() override;
    bool UpdateDown() override;
    void FinishDown() override;
    bool UpdateCancel() override;
    void StartCancel() override;
    void FinishCancel() override;

    /* 0x78 */ AnimatorSet* mNormalAnimators = nullptr;
    /* 0x80 */ AnimatorSet* mTouchAnimators = nullptr;
    /* 0x88 */ bool mUseTouch = false;
};
static_assert(sizeof(TwoTouchCheckKeepButton) == 0x90);

// A button of a group of buttons (CSV eui::UniteButton; 0x90 bytes, vtable 0x24c7a88 with 42 slots). `mType` is the
// value of the layout's "UniteButtonType" user data (0-5; its SEAD_ENUM text table is at 0x7100bdb868, the
// enumerator names are not known).
class UniteButton : public AnimButton {
public:
    NN_RUNTIME_TYPEINFO(AnimButton)
    const char* getClassName() const override { return "UniteButton"; }

    UniteButton();

    bool ProcessOn() override;
    void StartOn() override { AnimButton::StartOn(); }
    bool ProcessOff() override;
    bool ProcessCancel() override;
    bool UpdateDown() override;
    bool UpdateCancel() override;
    void StartDown() override;
    void StartCancel() override;
    void FinishDown() override;
    void FinishCancel() override;
    void Build(const nn::ui2d::ControlSrc& src, LayoutEx* layout) override;
    bool HitTest(const sead::Vector2f& pos) const override;
    void StartDrag(const sead::Vector2f& pos) override;
    void UpdateDrag(const sead::Vector2f* pos) override;
    void FinishDrag(const sead::Vector2f* pos) override;
    void BuildStateAnim(const nn::ui2d::ControlSrc& src, LayoutEx* layout) override;

    // Slot 41 (0x7100bdb254; the CSV names it CheckKeepButton::Uncheck)
    virtual void Uncheck();
    // 0x7100bdb2b0
    void ForceSetChecked(bool checked);

    /* 0x68 */ Animator* mCheckAnim = nullptr;
    /* 0x70 */ Animator* mDragAnim = nullptr;
    /* 0x78 */ sead::Vector2f mStartPos = {0, 0};
    /* 0x80 */ sead::Vector2f mPanePos = {0, 0};
    /* 0x88 */ u8 mType = 4;
    /* 0x89 */ bool mChecked = false;
    /* 0x8a */ bool mAllowX = true;
    /* 0x8b */ bool mAllowY = true;
};
static_assert(sizeof(UniteButton) == 0x90);

// A hover-only button (CSV eui::HoverButton; vtable 0x24c92d8; same size as AnimButton).
class HoverButton : public AnimButton {
public:
    NN_RUNTIME_TYPEINFO(AnimButton)
    const char* getClassName() const override { return "HoverButton"; }

    // 0x7100befdc4
    void Initialize(sead::Heap* heap, nn::ui2d::Pane* pane, Animator* anim, LayoutEx* layout);

    // Slot 7 (0x7100beff6c)
    void Down() override;
};
static_assert(sizeof(HoverButton) == 0x68);

// A button that only reacts to a tap (CSV eui::TapButton; vtable 0x24c9430; same size as AnimButton).
class TapButton : public AnimButton {
public:
    NN_RUNTIME_TYPEINFO(AnimButton)
    const char* getClassName() const override { return "TapButton"; }

    void On() override;
    void Off() override;
    void ForceOff() override;
    bool ProcessDown() override;
    void FinishDown() override;
};
static_assert(sizeof(TapButton) == 0x68);

}  // namespace eui
