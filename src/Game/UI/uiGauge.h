#pragma once
#include <container/seadPtrArray.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/UI/uiTimer.h"
namespace eui {
class Animator;
class CapturePane;
class LayoutEx;
class TraceGaugeControl;
}

// vtable 0x7102474fd8 (6 slots); placeholder generated from the vtable (genskel.py).
// ScreenPauseMenuInfo embeds Unk_7102475050 (0x130) at 0x36e0 and Unk_71024750c8 (0xe0) at 0x3810.
// The original destructor is inline (its D2 copy 0x71009479c4 sits in Unk_71024750c8's TU and both vtables use it;
// D0 0x71009453bc is in another TU); it is defined out of line here so that the vtable (and RTTI rows) stay emitted.
class Unk_7102474fd8 {
    SEAD_RTTI_BASE(Unk_7102474fd8)
public:
    virtual ~Unk_7102474fd8();
    virtual void m4();
    virtual s32 m5() { return 0; }

    // 0x7100945364 (inlined into the ScreenMainScreen3D / ScreenPauseMenuInfo constructors as well)
    Unk_7102474fd8();
    // 0x710094581c (declared only; 796 bytes): a state function stored in _a0
    void sub_710094581C();
    // 0x7100945c98 (placeholder name): closes the layout if it is open or opening; with `a1`, also when it is not
    // closed
    void sub_7100945C98(bool a1);
    // 0x7100945c34 (placeholder name): closes the layout if it is open or opening and hides its root pane
    void sub_7100945C34();
    // 0x7100946640 (placeholder name): stops the _40 animator at its maximum (`max`) or minimum
    void sub_7100946640(bool max);
    // 0x7100945db8 (placeholder name): resets the TU's gauge flags (unless sub_7100AA8F30 holds), flags the capture
    // panes of an open layout, runs the state function _a0 and clears _9d / _9e
    void sub_7100945DB8();
    // 0x7100945ea4 (placeholder name): follows the trace gauge: stores its speed in _98 while it is not tracing,
    // otherwise stops tracing at _98 (or once it has caught up)
    void sub_7100945EA4();
    // 0x7100945d70 (placeholder name): sets the trace gauge's tracing speed to its _50
    void sub_7100945D70();
    // 0x7100945d98 (placeholder name): the trace gauge's _6c flag (false without one)
    bool sub_7100945D98() const;
    // 0x7100946604 / 0x710094661c (placeholder names): set the alpha / uniform scale of the layout's root pane
    void sub_7100946604(u8 alpha);
    // 0x71009465d8 (placeholder name): moves the root pane to `position` (z = 0)
    void sub_71009465D8(const sead::Vector2f& position);
    void sub_710094661C(f32 scale);
    // 0x7100946664 (placeholder name): stops the _50 animator at its maximum (`max`) or minimum
    void sub_7100946664(bool max);
    // 0x7100946898 / 0x71009468ac (placeholder names): play the _28 / _58 animator
    void sub_7100946898();
    void sub_71009468AC();
    // 0x7100945d84 (placeholder name): sets the trace gauge's _6c flag
    void sub_7100945D84(bool value);
    // 0x7100946864 (placeholder name): 1 + the number of whole 1000s above 1000 in _8c
    s32 sub_7100946864() const;
    // 0x71009468e0 (placeholder name): stops the _58 animator at `frame`
    void sub_71009468E0(f32 frame);
    // 0x71009468c0 / 0x71009468d4: query the _58 animator (const spelling inferred).
    bool sub_71009468C0() const;
    f32 sub_71009468D4() const;

    // Layout from the constructor (0x8 .. 0x80 zeroed as one block) and the gauge updates 0x7100945f78 /
    // 0x7100946318 (placeholder types: the slots used are eui::Animator / TraceGaugeControl virtuals).
    /* 0x08 */ eui::LayoutEx* _8 = nullptr;
    /* 0x10 */ eui::TraceGaugeControl* _10 = nullptr;
    /* 0x18 */ eui::Animator* _18 = nullptr;
    /* 0x20 */ eui::Animator* _20 = nullptr;
    /* 0x28 */ eui::Animator* _28 = nullptr;
    /* 0x30 */ eui::Animator* _30 = nullptr;
    /* 0x38 */ eui::Animator* _38 = nullptr;
    /* 0x40 */ eui::Animator* _40 = nullptr;
    /* 0x48 */ eui::Animator* _48 = nullptr;
    /* 0x50 */ eui::Animator* _50 = nullptr;
    /* 0x58 */ eui::Animator* _58 = nullptr;
    // capture panes whose _db flag sub_7100945DB8 sets
    /* 0x60 */ sead::PtrArray<eui::CapturePane> _60;
    /* 0x70 */ void* _70 = nullptr;
    /* 0x78 */ void* _78 = nullptr;
    /* 0x80 */ f32 _80 = 1.0f;
    /* 0x84 */ bool _84 = false;
    /* 0x88 */ f32 _88 = 0;
    /* 0x8c */ f32 _8c = 0;
    /* 0x90 */ f32 _90 = 0;
    /* 0x94 */ f32 _94 = 0;
    // the value the trace gauge catches up to (sub_7100945EA4)
    /* 0x98 */ f32 _98 = 0;
    /* 0x9c */ bool _9c = false;
    /* 0x9d */ bool _9d = false;
    /* 0x9e */ bool _9e = false;
    // a member function pointer (Unk_7102475050::m12 compares it with sub_710094581C)
    /* 0xa0 */ void (Unk_7102474fd8::*_a0)() = nullptr;
    /* 0xb0 */ void* _b0 = nullptr;
};

// 0x71009452c4 (placeholder name): the gauge flag sUnk_71025d64ec of the gauge TU
bool sub_71009452C4();

// Placeholder: the common base of Unk_7102475050 and Unk_71024750c8. Both vtables have the slots m6 .. m12 after the
// base's six, and the gauge helpers 0x7100945f78 / 0x7100946740 (in the base's TU) call m6 .. m9 and m12 on `this`;
// it has no RTTI of its own (both derived classes check Unk_7102474fd8 directly) and no vtable of its own in the
// original (abstract).
class Unk_7102474fd8Gauge : public Unk_7102474fd8 {
public:
    virtual f32 m6() = 0;
    virtual f32 m7() = 0;
    virtual f32 m8() = 0;
    virtual f32 m9(f32 value) = 0;
    virtual bool m10() = 0;
    virtual void m11() = 0;
    virtual void m12() = 0;

    // 0x7100945f78 (placeholder name): takes the new gauge value (m7), moves the gauge animation and the trace
    // gauge, then updates the extra animators
    void sub_7100945F78();
    // 0x71009461b8 (placeholder name): with m10, opens the layout (also when the remote bomb / camera rune state
    // says so) after refreshing the gauge; otherwise closes it
    void sub_71009461B8();
    // 0x7100946318 (declared only; 304 bytes): sets the animators _50 / _40 / _20 from the player's state
    void sub_7100946318();
    // 0x7100945d04 (placeholder name): stores the gauge value and stops the _18 animator at its scaled frame
    void sub_7100945D04(f32 value);
    // 0x710094574c / 0x71009457b4 (placeholder names): set the trace gauge's tracing speed / _50 from `value`
    // (scaled against m8 by uking::ui::sub_7100AA8FCC)
    void sub_710094574C(f32 value);
    void sub_71009457B4(f32 value);
    // 0x7100946740 (placeholder name): opens the layout (and with `update`, refreshes the gauge first) if it is
    // closed or closing; with `a1` also when it is not open
    void sub_7100946740(bool a1, bool update);
};

// vtable 0x7102475050 (13 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102475050 : public Unk_7102474fd8Gauge {
    SEAD_RTTI_OVERRIDE(Unk_7102475050, Unk_7102474fd8)
public:
    ~Unk_7102475050() override;
    // 0x71009468f0: also creates the "Born" (stopped at min) / "Dead" (stopped at max) animators and ends the timer
    void m4() override;
    // the gauge values from the UI Manager (uking::ui::sub_7100A9B6D0 / sub_7100A9B6F0)
    f32 m6() override;
    f32 m7() override;
    // 3000 (the default limit set by uking::ui::sub_7100945320)
    f32 m8() override;
    // (value - 1000) / 2000 clamped to [0, 1]
    f32 m9(f32 value) override;
    // 0x71009469b4 (not decompiled)
    bool m10() override;
    // 0x7100946a5c (placeholder name): whether the timer _c8 is still running
    bool sub_7100946A5C() const;
    // 0x7100946688: restarts the timer while the value changes; plays _30 once the value is stable
    void m11() override;
    // 0x71009467d8: closes the layout once the value is stable and the state is sub_710094581C
    void m12() override;
    s32 m5() override { return 5; }

    // No-argument bool callbacks bound by the native ScreenPauseMenuInfo constructor.
    bool sub_7100946A7C();
    bool sub_7100946F88();
    // Both callbacks pass their Animator; the body updates this leaf's translation/state.
    bool sub_7100946BE8(eui::Animator* animator);

    /* 0xb8 */ eui::Animator* _b8 = nullptr;
    /* 0xc0 */ eui::Animator* _c0 = nullptr;
    /* 0xc8 */ uking::ui::UiTimer _c8;
    // 9470cc / 947188 save root pane translation x/y; 946be8 computes Euclidean distance.
    /* 0xe0 */ sead::Vector2f _e0 = sead::Vector2f::zero;
    /* 0xe8 */ s32 _e8 = 4;
    /* 0xf0 */ sead::DelegateR<Unk_7102475050, bool> _f0{this, &Unk_7102475050::sub_7100946A7C};
    /* 0x110 */ sead::DelegateR<Unk_7102475050, bool> _110{this, &Unk_7102475050::sub_7100946F88};
};

// vtable 0x71024750c8 (13 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024750c8 : public Unk_7102474fd8Gauge {
    SEAD_RTTI_OVERRIDE(Unk_71024750c8, Unk_7102474fd8)
public:
    ~Unk_71024750c8() override;
    // 0x7100947244: also stops _40 at its minimum and drops it
    void m4() override;
    // the gauge value from the UI Manager (uking::ui::sub_7100A9B710)
    f32 m6() override;
    // 1000 or 2000 depending on m6() (0 while it is not positive)
    f32 m7() override;
    // 2000 (the default limit set by uking::ui::sub_7100945344)
    f32 m8() override;
    // how many 1000 steps _8c is above 1000 (the parameter is unused)
    f32 m9(f32 value) override;
    // 0x7100947318 (not decompiled)
    bool m10() override;
    void m11() override {}
    void m12() override {}
    s32 m5() override { return 10; }

    bool sub_7100947520();
    // The ctor does not initialize this state word; do not add a default.
    /* 0xb8 */ s32 _b8;
    /* 0xc0 */ sead::DelegateR<Unk_71024750c8, bool> _c0{this, &Unk_71024750c8::sub_7100947520};
};
static_assert(sizeof(Unk_7102474fd8) == 0xb8);
static_assert(sizeof(sead::DelegateR<Unk_7102475050, bool>) == 0x20);
static_assert(alignof(sead::DelegateR<Unk_7102475050, bool>) == 8);
static_assert(sizeof(Unk_7102475050) == 0x130);
static_assert(sizeof(Unk_71024750c8) == 0xe0);

