#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <prim/seadSafeString.h>

// Placeholder classes whose only member is a virtual destructor (vtable = [D1, D0], D1 empty): the
// original keeps them as members / locals of the screens. Named after their vtable (symbol start).

namespace eui {
class Animator;
}

namespace eui {
class Animator;
class LayoutEx;
class TextBoxEx;
}  // namespace eui

namespace uking::ui {

class Unk_7102474b38 {
public:
    virtual ~Unk_7102474b38();
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
    virtual ~Unk_7102474ba8();

    u8 _8[0x10];  // sizeof is 0x18 (array element of ScreenMessageGet::_37d8)
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

private:
    /* 0x8 */ u64 _8{};
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
    /* 0x940 */ s32 _940 = 0;
    /* 0x944 */ f32 _944 = 30.0f;
    /* 0x948 */ f32 _948 = 30.0f;
    /* 0x94c */ f32 _94c = 0.1f;
    /* 0x950 */ f32 _950 = 0.2f;
    /* 0x954 */ s32 _954 = 0;
    /* 0x958 */ f32 _958 = 15.0f;
    /* 0x95c */ u8 _95c = 1;
    /* 0x95d */ u8 _95d = 0;
    /* 0x95e */ u16 _95e = 0;
    /* 0x960 */ u64 _960 = 30;
};

class Unk_7102474c08 {
public:
    virtual ~Unk_7102474c08();
};

class Unk_7102474c28 {
public:
    virtual ~Unk_7102474c28();
};

class Unk_7102474c48 {
public:
    virtual ~Unk_7102474c48();
};

class Unk_7102475158 {
public:
    virtual ~Unk_7102475158();
};

class Unk_7102475278 {
public:
    virtual ~Unk_7102475278();
};

class Unk_7102475348 {
public:
    virtual ~Unk_7102475348();
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

class Unk_7102476d68 {
public:
    virtual ~Unk_7102476d68();
};

class Unk_7102477468 {
public:
    virtual ~Unk_7102477468();
};

class Unk_7102477488 {
public:
    virtual ~Unk_7102477488();
};

class Unk_71024774c8 {
public:
    virtual ~Unk_71024774c8();
};

class Unk_7102477508 {
public:
    virtual ~Unk_7102477508();
};

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
    virtual ~Unk_710247aa30();
};

class Unk_710247adc8 {
public:
    virtual ~Unk_710247adc8();

    u8 _8[0x38];  // sizeof is 0x40 (ScreenMessageGet::_3670 is an array of two)
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
    virtual ~Unk_710247dc70();
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

    void* _8;
    sead::SafeString _10 = sead::SafeString::cEmptyString;
    sead::SafeString _20 = sead::SafeString::cEmptyString;
    sead::SafeString _30 = sead::SafeString::cEmptyString;
    sead::SafeString _40 = sead::SafeString::cEmptyString;
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
    virtual ~Unk_71024774a8();
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

class Unk_7102474df8 {
public:
    virtual ~Unk_7102474df8();

    u64 _8;
    sead::PtrArray<Unk_Elem> _10;
};

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

    /* 0x8 */ s32 _8 = 0;
    /* 0x10 */ sead::FixedSafeString<256> _10;
    /* 0x128 */ u8 _128 = 0;
    /* 0x130 */ sead::Buffer<UiSlot> _130;
    sead::Buffer<Unk_Elem2> _140;
    /* 0x150 */ u16 _150 = 0;
};

// Member of several screens (0x28 bytes, e.g. ScreenAppHome 0x38a0 ... 0x3918): virtual destructor and one more
// virtual function (0x7100937e9c, not decompiled).
class Unk_7102474dd0 {
public:
    virtual ~Unk_7102474dd0();
    virtual void m2();

    u8 _8[0x20];
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

    u8 _8[0x88]{};
};

}  // namespace uking::ui
