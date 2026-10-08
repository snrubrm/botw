#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include "Game/UI/uiTimer.h"

// Small screen members and controllers named after their original vtable.
// Several retain only their recovered destructor pair; recovered layouts and helpers are below.

namespace nn::ui2d {
class Pane;
class Material;
}

namespace sead {
class Heap;
}

namespace eui {
class UniteButton;
class Animator;
class LayoutEx;
class TextBoxEx;
}  // namespace eui

namespace uking::ui {

class Screen;

class Unk_7102474b38 {
public:
    Unk_7102474b38();
    virtual ~Unk_7102474b38();
    void sub_7100932F74(eui::LayoutEx* first, eui::LayoutEx* second);
    eui::LayoutEx* sub_7100932F7C(s32 index) const;
    void sub_7100932FA8(s32 index, eui::LayoutEx* layout, bool flag);
    void sub_7100932FDC(s32 index, bool animated);
    bool sub_7100933038(s32 index) const;
    void sub_710093307C(s32 index, nn::ui2d::Pane* parent);
    void sub_71009330E4();

private:
    eui::LayoutEx* mFirst = nullptr;
    eui::LayoutEx* mSecond = nullptr;
};

// Member of the number-display screens (Kolog / Akash / Mamo / DLCSinJuAkashi: at 0x3638, Mamo also at 0x3678).
class Unk_7102474b78 {
public:
    Unk_7102474b78();
    virtual ~Unk_7102474b78();

    // 0x71009331c (declared only; sets up the 'T_RupeeGhost_00' / 'GhostIn' / 'PlusMinus' members from the counter's
    // parts layout and its text box)
    void sub_71009331C(eui::LayoutEx* layout, eui::TextBoxEx* text);

    // 0x71009333a4 / 0x71009333c4 (placeholder names): store the 'Flash' animator / a counter value
    void set30(eui::Animator* animator);
    void set38(s32 value);
    // 0x71009333ac (placeholder name): `if (_20) _20->StopAtMin()`; 0x71009333cc (declared only; 436 bytes)
    void sub_71009333AC();
    void sub_71009333CC();

    /* 0x08 */ eui::LayoutEx* _8{};
    /* 0x10 */ eui::TextBoxEx* _10{};
    /* 0x18 */ eui::TextBoxEx* _18{};
    /* 0x20 */ eui::Animator* _20{};
    /* 0x28 */ eui::Animator* _28{};
    /* 0x30 */ eui::Animator* _30{};
    /* 0x38 */ s32 _38{};
    /* 0x3c */ u8 _3c{};
};

class Unk_7102474ba8 {
public:
    Unk_7102474ba8();
    virtual ~Unk_7102474ba8();
    void sub_710093372C(bool first);
    void sub_7100933774(bool first);
    bool sub_71009337B0() const;
    void sub_71009337D4(nn::ui2d::Pane* parent);
    bool sub_7100933828(const nn::ui2d::Pane* parent) const;
    void sub_7100933850(bool reverse, bool animated);

    // Producer 9336AC attaches the layout and creates its animator.
    eui::LayoutEx* _8 = nullptr;
    eui::Animator* _10 = nullptr;
};

// A UI element helper that drives three animators (placeholder layout; the CSV rows 0x7100935894 - 0x71009359d8 are
// small non-virtual methods; names after the offsets).
class Unk_7102474be8 {
public:
    Unk_7102474be8();
    virtual ~Unk_7102474be8();

    void set940(s32 value);
    void set944(f32 value);
    void set948(f32 value);
    void set958(f32 value);
    void playAnimator918();
    void stopAnimator918();
    void playAnimator8e0();
    void stopAnimator8e0();
    bool isAnimator8e0Playing() const;
    f32 getAnimator8e0Frame() const;
    void playAnimator8e0FromFrame(f32 frame);
    void playAnimator910();
    bool isAnimator910Playing() const;
    void stopAnimator910(f32 frame);
    void sub_71009359E8();
    // 0x7100934b94 (declared only): attaches the gauge to `layout`
    void sub_7100934B94(eui::LayoutEx* layout, bool flag);
    // inline-only in the original; name is a guess (three screens store the byte right after the setup)
    void set95c(bool on) { _95c = on; }
    // inline-only in the original; name is a guess (MainScreenMS / HeartIchigekiDLC m100 copy `_948` into `_944`)
    f32 get948() const { return _948; }
    // 0x710093515c (declared only; 9 callers): advances the gauge by the screen's animation step
    void sub_710093515C(f32 step);
    // 0x7100935180 (declared only): integrates _944 toward _93c with sound triggers
    void sub_7100935180(f32 step);
    // 0x7100935384 (declared only): post-step gauge/animation update
    void sub_7100935384();

private:
    friend class Unk_7102474c08;
    /* 0x8 */ eui::LayoutEx* _8{};
    u8 _10[0x8e0 - 0x10];
    /* 0x8e0 */ eui::Animator* _8e0{};
    u8 _8e8[0x910 - 0x8e8]{};
    /* 0x910 */ eui::Animator* _910{};
    /* 0x918 */ eui::Animator* _918{};
    u8 _920[0x928 - 0x920]{};
    /* 0x928 */ s32 _928 = 30;
    /* 0x92c */ f32 _92c = 30.0f;
    /* 0x930 */ s32 _930 = 0;
    /* 0x934 */ f32 _934 = 30.0f;
    /* 0x938 */ s32 _938 = 30;
    /* 0x93c */ f32 _93c = 30.0f;
    /* 0x940 */ u32 _940 = 0;
    /* 0x944 */ f32 _944 = 30.0f;
    /* 0x948 */ f32 _948 = 30.0f;
    /* 0x94c */ f32 _94c = 0.1f;
    /* 0x950 */ f32 _950 = 0.2f;
    /* 0x954 */ f32 _954 = 0.0f;
    /* 0x958 */ f32 _958 = 15.0f;
    /* 0x95c */ u8 _95c = 1;
    /* 0x95d */ u8 _95d = 0;
    /* 0x95e */ u8 _95e = 0;
    /* 0x95f */ u8 _95f = 0;
    /* 0x960 */ s32 _960 = 30;
    /* 0x964 */ s32 _964 = 0;
};

class Unk_71025d6578;

class Unk_7102474c08 {
public:
    Unk_7102474c08();
    virtual ~Unk_7102474c08();
    void sub_71009367C4(bool first);
    void sub_7100936830(bool first);
    bool sub_71009368A4() const;
    bool sub_71009368C8() const;
    void sub_71009368EC(f32 step);
    void sub_710093694C();
    f32 sub_710093695C() const;

private:
    Unk_7102474be8* mGauge = nullptr;
    Unk_71025d6578* _10 = nullptr;
    bool _18 = false;
    u8 _19 = 0;
    UiTimer _1c;
};

class Unk_7102474c28 {
public:
    Unk_7102474c28();
    virtual ~Unk_7102474c28();
    void sub_7100936998(eui::LayoutEx* layout);
    void sub_7100936A28(s32 value);
    void sub_7100936A7C(s32 value);
    void sub_7100936AD8();

private:
    eui::LayoutEx* mLayout = nullptr;
    eui::Animator* mPageAnimator = nullptr;
    eui::Animator* mScrollAnimator = nullptr;
    f32 mPageStep = 0;
    f32 mScrollStep = 0;
    s32 mPageValue = 0;
};

class Unk_7102474c48 {
public:
    virtual ~Unk_7102474c48();
    void sub_7100936B18(eui::LayoutEx* layout);
    void sub_7100936B7C(bool first, bool second);

private:
    eui::LayoutEx* mLayout;
    eui::Animator* mAnimator;
    bool mActive;
};

class Unk_7102475158 {
public:
    virtual ~Unk_7102475158();
};

// A small parameter block (size >= 0x68; placeholder layout and accessor names after the offsets: the CSV rows
// 0x7100950244 - 0x71009502f0 are its non-virtual getters / setters).
class Unk_7102475368 {
public:
    struct Pair {
        s32 a;
        s32 b;
    };

    virtual ~Unk_7102475368();

    u8* get10();
    void set18(const Pair& value);
    Pair* get18();
    void set20(const Pair& value);
    Pair* get20();
    void set28(f32 value);
    f32 get28() const;
    void set2c(f32 value);
    f32 get2c() const;
    u8* get30();
    void set38(f32 value);
    f32 get38() const;
    void set3c(f32 value);
    f32 get3c() const;
    void set40(const Pair& value);
    Pair* get40();
    s32 get48() const;
    u8* get60();

private:
    u8 _8[8];
    /* 0x10 */ u8 _10[8];
    /* 0x18 */ Pair _18;
    /* 0x20 */ Pair _20;
    /* 0x28 */ f32 _28;
    /* 0x2c */ f32 _2c;
    /* 0x30 */ u8 _30[8];
    /* 0x38 */ f32 _38;
    /* 0x3c */ f32 _3c;
    /* 0x40 */ Pair _40;
    /* 0x48 */ s32 _48;
    u8 _4c[0x60 - 0x4c];
    /* 0x60 */ u8 _60[8];
};

class Unk_7102475388 {
public:
    virtual ~Unk_7102475388();
};

class Unk_71024753a8 {
public:
    virtual ~Unk_71024753a8();
};

class Unk_7102476a80 {
public:
    virtual ~Unk_7102476a80();
};

class Unk_7102476b20 {
public:
    virtual ~Unk_7102476b20();
};

class Unk_7102476b40 {
public:
    virtual ~Unk_7102476b40();
};

class Unk_7102476b60 {
public:
    virtual ~Unk_7102476b60();
};

class Unk_7102477468 {
public:
    Unk_7102477468();
    virtual ~Unk_7102477468();
    void sub_7100987FBC(eui::UniteButton* button);
    void sub_7100988010(u32 frame);
    void sub_710098802C(bool checked);
    bool sub_7100988040() const;
    void sub_7100988060(bool play);
    bool sub_710098807C() const;

    eui::UniteButton* mButton = nullptr;
    eui::Animator* mIconAnimator = nullptr;
};
static_assert(sizeof(Unk_7102477468) == 0x18);

class Unk_7102477488 {
public:
    Unk_7102477488();
    virtual ~Unk_7102477488();
    void sub_71009880AC(eui::UniteButton* button);
    void sub_71009880E8(u32 frame);
    eui::UniteButton* sub_7100988104() const;
    eui::LayoutEx* sub_710098810C() const;
    void sub_7100988138(bool on);
    void sub_7100988154(bool checked);

    eui::UniteButton* mButton = nullptr;
    eui::Animator* mPatternAnimator = nullptr;
};
static_assert(sizeof(Unk_7102477488) == 0x18);

class Unk_71024774c8 {
public:
    Unk_71024774c8();
    virtual ~Unk_71024774c8();
    void sub_7100988EF0(eui::LayoutEx* layout);
    void sub_7100988F30(f32 frame);
    void sub_7100988FE8();

    eui::LayoutEx* mLayout = nullptr;
    eui::Animator* mTexturePatternAnimator = nullptr;
};
static_assert(sizeof(Unk_71024774c8) == 0x18);

class Unk_7102477508 {
public:
    Unk_7102477508();
    virtual ~Unk_7102477508();
    void sub_7100989A80(eui::LayoutEx* layout);
    void sub_7100989AF0(s32 category, s32 value, s32 number);
    void sub_7100989C0C(s32 value);

    eui::LayoutEx* mLayout = nullptr;
    eui::Animator* mCategoryAnimator = nullptr;
    eui::Animator* mHeartMarkOffAnimator = nullptr;
    eui::Animator* mNumberAnimator = nullptr;
};
static_assert(sizeof(Unk_7102477508) == 0x28);

class Unk_7102479bb0 {
public:
    virtual ~Unk_7102479bb0();
};

class Unk_7102479f90 {
public:
    virtual ~Unk_7102479f90();
};

class Unk_7102479fb0 {
public:
    virtual ~Unk_7102479fb0();
};

class Unk_710247aa30 {
public:
    Unk_710247aa30();
    virtual ~Unk_710247aa30();
    void sub_71009B14F8(eui::LayoutEx* layout);
    void sub_71009B1578(s32 state);
    void sub_71009B163C(s32 state, f32 frame);
    nn::ui2d::Pane* sub_71009B170C() const;
    nn::ui2d::Material* sub_71009B1738() const;
    f32 sub_71009B1784() const;

    eui::LayoutEx* mLayout = nullptr;
    eui::Animator* mBreakLoopAnimator = nullptr;
    eui::Animator* mNewAnimator = nullptr;
};
static_assert(sizeof(Unk_710247aa30) == 0x20);

class Unk_710247adc8 {
public:
    Unk_710247adc8();
    virtual ~Unk_710247adc8();
    void sub_71009B205C(eui::LayoutEx* layout);
    void sub_71009B20E4(u32 category, s32 value, s32 old_number);
    void sub_71009B21B4(s32 value, bool old);

    /* 0x08 */ eui::LayoutEx* mLayout = nullptr;
    /* 0x10 */ eui::Animator* mTexturePatternAnimator = nullptr;
    /* 0x18 */ eui::Animator* mColorAnimator = nullptr;
    /* 0x20 */ eui::Animator* mNumberAnimator = nullptr;
    /* 0x28 */ eui::Animator* mOldNumberAnimator = nullptr;
    u8 _30[0x10];
};

class Unk_710247ae08 {
public:
    virtual ~Unk_710247ae08();
};

class Unk_710247ae28 {
public:
    virtual ~Unk_710247ae28();
};

class Unk_710247d8d8 {
public:
    virtual ~Unk_710247d8d8();
};

class Unk_710247dc50 {
public:
    virtual ~Unk_710247dc50();
};

class Unk_710247dc70 {
public:
    Unk_710247dc70();
    virtual ~Unk_710247dc70();

    /* 0x8 */ u64 _8 = 0;
    /* 0x10 */ u64 _10 = 0;
};

class Unk_71024810d8 {
public:
    virtual ~Unk_71024810d8();
};

class Unk_71024810f8 {
public:
    virtual ~Unk_71024810f8();
};

class Unk_7102481118 {
public:
    virtual ~Unk_7102481118();
};

class Unk_7102481e50 {
public:
    virtual ~Unk_7102481e50();
};

class Unk_710249c3b0 {
public:
    virtual ~Unk_710249c3b0();
};

class Unk_710249c3d0 {
public:
    virtual ~Unk_710249c3d0();
};

class Unk_710249c3f0 {
public:
    virtual ~Unk_710249c3f0();
};

class Unk_710249c410 {
public:
    virtual ~Unk_710249c410();
};

class Unk_7102516880 {
public:
    virtual ~Unk_7102516880();
};

// With a user-provided (empty) destructor: the original D1 keeps the vtable store.
class Unk_7102474b58 {
public:
    explicit Unk_7102474b58(void* owner);
    virtual ~Unk_7102474b58();

    // The index is a SEAD_ENUM in the original (a 4-byte class passed in x1; `operator int() const volatile` spills it).
    SEAD_ENUM(Index, _0, _1)

    // 0x71009319c: copies the two strings into entry `index`.
    void sub_71009319C(Index index, const sead::SafeString& a, const sead::SafeString& b);
    // 0x71009331e8 (172 bytes) / 0x7100933294 (92 bytes): declared only (placeholder names)
    void sub_71009331E8(Index index);
    void sub_7100933294();

    struct Entry {
        sead::SafeString a = sead::SafeString::cEmptyString;
        sead::SafeString b = sead::SafeString::cEmptyString;
    };

    void* _8;
    sead::SafeArray<Entry, 2> _10;
    u64 _50{};
};

class Unk_7102476a40 {
public:
    virtual ~Unk_7102476a40();
};

class Unk_7102476a60 {
public:
    virtual ~Unk_7102476a60();
};

class Unk_7102476b00 {
public:
    virtual ~Unk_7102476b00();
};

class Unk_71024774a8 {
public:
    Unk_71024774a8();
    virtual ~Unk_71024774a8();
    void sub_71009884A8(eui::LayoutEx* layout);
    void sub_71009884B0();
    void sub_7100988AF4(bool open);
    f32 sub_7100988D00(s32 index) const;
    bool sub_7100988D1C(s32 index) const;
    bool sub_7100988D60(s32 index) const;
    void sub_7100988D84(s32 index, f32 frame);
    void sub_7100988DA0(s32 index, f32 speed);
    void sub_7100988DC4();
    void sub_7100988DD0(const sead::Vector2f& position);

    /* 0x08 */ eui::LayoutEx* mLayout;
    /* 0x10 */ sead::SafeArray<eui::Animator*, 9> mAnimators;
    /* 0x58 */ f32 _58;
    /* 0x5c */ u8 _5c;
    u8 _5d[3];
    /* 0x60 */ sead::FixedSafeString<64> _60;
};

class Unk_71024810b8 {
public:
    virtual ~Unk_71024810b8();
};

// Member of ScreenTitle (0x3688; 0xa0 bytes: three FixedSafeString<16> and other data; the 0x7100a82fbc ctor is not decompiled).
// Polymorphic base of Unk_710249d300 (its `_8` is stored before the derived class' members).
class Unk_710249d300Base {
public:
    virtual ~Unk_710249d300Base() = default;

    s32 _8 = 0;
};

class Unk_710249d300 : public Unk_710249d300Base {
public:
    Unk_710249d300();
    ~Unk_710249d300() override;

    u8 _c[4];
    // Small fields (meaning unknown; the original stores both initial values as one merged 64-bit constant).
    u32 _10 = 0x11e000;
    u32 _14 = 0x01007ef0;
    u16 _18 = 0;
    sead::FixedSafeString<16> _20 = sead::SafeString::cEmptyString;
    sead::FixedSafeString<16> _48 = sead::SafeString::cEmptyString;
    sead::FixedSafeString<16> _70 = sead::SafeString::cEmptyString;
    u8 _98 = 0;
    s32 _9c = 0;
};

// Opaque element type of the PtrArray members below.
struct Unk_Elem;

class Unk_7102474dd0;

// Setup record for Unk_7102474df8::sub_7100937FA4 (0x1c bytes; built on the stack by the owning screens).
struct Unk_7102474df8_Params {
    s32 direction = 1;        // → _34
    f32 spacing = 50.0f;      // → _38
    sead::Vector2f corner1;   // → _3c
    sead::Vector2f corner2;   // → _44
    s32 count = 0;            // → _4c
};

// Scroll smoothing parameters (0xc bytes; the first 8 bytes are copied whole by 0x7100937FA4).
struct Unk_7102474df8_Speeds {
    struct Pair {
        f32 factor = 0.28f;  // → _50: scaled by the step in the update
        f32 max = 300.0f;    // → _54: clamps the per-frame scroll delta
    };
    Pair pair;
    f32 threshold = 0.1f;  // → _58: dead zone for the scroll delta
};

// Scroll-list controller (member of several screens, e.g. ScreenSousaGuide at 0x3610). The setup function
// 0x7100937fa4 fills it from a parameter record; 0x7100938408 registers Unk_7102474dd0 entries with it.
class Unk_7102474df8 {
public:
    // 0x7100937eec
    Unk_7102474df8();
    virtual ~Unk_7102474df8();

    // 0x7100937fa4: copy the setup record and speeds, allocate the entry list, center _20 on the corners
    void sub_7100937FA4(sead::Heap* heap, Screen* screen, const Unk_7102474df8_Params* params,
                        const Unk_7102474df8_Speeds* speeds);
    // 0x7100937c74: pick the scroll direction from _2c/_28 and arm the direction callback
    void sub_7100937C74();
    // 0x7100938090 (declared only): advance _2c toward _30 and reposition every entry
    void sub_7100938090(f32 step);
    // 0x71009382b8 (declared only): direction helper using _5c/_60/_64/_68
    bool sub_71009382B8(f32 step);
    // 0x7100938294 (placeholder name): whether the distance _2c - _30 lies within [-x, x]
    bool sub_7100938294(f32 x) const;
    // 0x7100938408: assign the entry its offset from _34 (direction) and _38 (spacing) and push it into _10
    void sub_7100938408(Unk_7102474dd0* entry);

    /* 0x08 */ Screen* _8 = nullptr;
    /* 0x10 */ sead::PtrArray<Unk_7102474dd0> _10;
    /* 0x20 */ sead::Vector2f _20 = sead::Vector2f::zero;
    /* 0x28 */ f32 _28 = 0.0f;
    /* 0x2c */ f32 _2c = 0.0f;
    /* 0x30 */ f32 _30 = 0.0f;
    /* 0x34 */ s32 _34 = 1;      // direction: 0 down, 1 up, 2 left, 3 right
    /* 0x38 */ f32 _38 = 50.0f;  // spacing accumulated into _28 per registered entry
    /* 0x3c */ sead::Vector2f _3c = {0, 0};
    /* 0x44 */ sead::Vector2f _44 = {0, 0};
    /* 0x4c */ s32 _4c = 0;
    /* 0x50 */ Unk_7102474df8_Speeds _50;
    /* 0x5c */ sead::Vector2f _5c = sead::Vector2f::zero;
    /* 0x64 */ f32 _64 = 0.0f;
    /* 0x68 */ s32 _68 = 3;
    /* 0x6c */ u32 _6c;  // never initialized (padding)
    // Called by sub_7100938090 through the AArch64 member-function-pointer sequence (null check on the pointer
    // and the virtual bit, this-adjust by adj >> 1), then reset to null.
    /* 0x70 */ bool (Unk_7102474df8::*_70)(f32) = nullptr;
    /* 0x80 */ u8 _80 = 0;
};
static_assert(sizeof(Unk_7102474df8) == 0x88);
static_assert(sizeof(Unk_7102474df8_Params) == 0x1c);
static_assert(sizeof(Unk_7102474df8_Speeds) == 0xc);

// Element type of Unk_7102474bc8::_140: an inline empty destructor, so `delete[]` keeps the array cookie.
struct Unk_Elem2 {
    ~Unk_Elem2() {}
};

// A string record of the UI helper classes (0x128 bytes; placeholder name). Its constructor (0x7100934a6c) is called
// from 55 places.
struct UiStringEntry {
    UiStringEntry();

    /* 0x0 */ s32 _0 = -1;
    /* 0x8 */ sead::FixedSafeString<256> _8;
    /* 0x120 */ s32 _120 = 30;
    /* 0x124 */ s32 _124 = -1;
};

// A slot of Unk_7102474bc8 (placeholder names): a pointer to an object with an s32 at 0x104 and one more word.
struct UiSlotTarget {
    u8 _0[0x104];
    s32 _104;
};
struct UiSlot {
    UiSlotTarget* target;
    u64 _8;
};

// Member of ScreenSousaGuide (0x3618) and others: two sead::Buffers freed in the destructor (0x158 bytes).
class Unk_7102474bc8 {
public:
    // 0x71009338a0
    Unk_7102474bc8();
    virtual ~Unk_7102474bc8();

    // 0x7100933e50 / 0x7100933fb8 (placeholder names): `_130` holds `_8` slots (16 bytes each).
    bool sub_7100933E50() const;
    void sub_7100933FB8(u32 index, UiSlotTarget* target);

    // 0x7100933fe0 (declared only; 35 callers) / 0x7100934308 (32 callers): adds a string record (id, text, value)
    void sub_7100933FE0(const UiStringEntry& entry);
    void sub_7100934308(s32 id, const sead::SafeString& text, s32 value);

    /* 0x8 */ s32 _8 = 0;
    /* 0x10 */ sead::FixedSafeString<256> _10;
    /* 0x128 */ u8 _128 = 0;
    /* 0x130 */ sead::Buffer<UiSlot> _130;
    sead::Buffer<Unk_Elem2> _140;
    /* 0x150 */ u16 _150 = 0;
};

// Placeholder for the pane-like object Unk_7102474dd0 positions (a translation at 0x30 and a dirty bit in the byte at 0x58).
struct Unk_PaneTransform {
    u8 _0[0x30];
    sead::Vector2f _30;
    f32 _38;
    u8 _3c[0x58 - 0x3c];
    u8 _58;
};

// Member of several screens (0x28 bytes, e.g. ScreenAppHome 0x38a0 ... 0x3918): a position (`_18` + the offsets
// passed to m2) applied to one object.
class Unk_7102474dd0 {
public:
    // 0x7100937d74 (CSV unnamed): the constructor (vtable + null link + zero vectors)
    Unk_7102474dd0();
    virtual ~Unk_7102474dd0();
    // 0x7100937e9c
    virtual void m2(const sead::Vector2f& a, const sead::Vector2f& b);

    // set to the owning Unk_7102474df8 by 0x7100938408
    Unk_7102474df8* _8 = nullptr;
    Unk_PaneTransform* _10 = nullptr;
    sead::Vector2f _18 = sead::Vector2f::zero;
    sead::Vector2f _20 = sead::Vector2f::zero;
};
static_assert(sizeof(Unk_7102474dd0) == 0x28);

// vtable 0x7102493bd0: the same position applied to a list of objects (the PauseMenu screen's own member).
class Unk_7102493bd0 : public Unk_7102474dd0 {
public:
    ~Unk_7102493bd0() override;
    // 0x7100a3eca4
    void m2(const sead::Vector2f& a, const sead::Vector2f& b) override;

    sead::Buffer<Unk_PaneTransform*> _28;
    s32 _38;
};

// Element of ScreenOptionWindow::_3698 (owned by the screen; `delete` destroys the member at 0x70).
struct Unk_OptionWindowEntry {
    u8 _0[0x70];
    Unk_7102474dd0 _70;
};

// Member of ScreenMessageTips (0x318, 0x90 bytes). Vtable 0x7102509148; the constructor (0x71010a7bcc) clears the 0x88
// bytes after the vtable pointer. Declared only.
class Unk_7102509148 {
public:
    Unk_7102509148();
    virtual ~Unk_7102509148();

    // 0x71010a7ca4 / 0x71010a7edc (declared only): attach the tips layout / the amiibo tips layout and its animator
    void sub_71010A7CA4(eui::LayoutEx* layout);
    void sub_71010A7EDC(eui::LayoutEx* layout, eui::Animator* animator);

    u8 _8[0x88]{};
};

}  // namespace uking::ui
