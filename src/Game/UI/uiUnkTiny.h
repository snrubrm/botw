#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <prim/seadSafeString.h>

// Placeholder classes whose only member is a virtual destructor (vtable = [D1, D0], D1 empty): the
// original keeps them as members / locals of the screens. Named after their vtable (symbol start).

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

    u8 _8[0x35 - 0x8]{};
    u8 _35[8]{};
};

class Unk_7102474ba8 {
public:
    virtual ~Unk_7102474ba8();

    u8 _8[0x10];  // sizeof is 0x18 (array element of ScreenMessageGet::_37d8)
};

class Unk_7102474be8 {
public:
    virtual ~Unk_7102474be8();
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

class Unk_7102475368 {
public:
    virtual ~Unk_7102475368();
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

// Member of ScreenSousaGuide (0x3618) and others: two sead::Buffers freed in the destructor (0x158 bytes).
class Unk_7102474bc8 {
public:
    // 0x71009338a0 (declared only)
    Unk_7102474bc8();
    virtual ~Unk_7102474bc8();

    u8 _8[0x128];
    sead::Buffer<u8> _130;
    sead::Buffer<Unk_Elem2> _140;
    u8 _150[8];
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
