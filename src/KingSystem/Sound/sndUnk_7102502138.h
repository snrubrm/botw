#pragma once

#include <basis/seadTypes.h>
#include <container/seadObjList.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::xlink {
class XLink;
}

namespace ksys::snd {

// Placeholder (the object at Unk68+0x480). Its declared-only method 0x12c5034 (28 B) stores a level derived from its
// argument in `_10`.
// Placeholder type named after its method at 0x71012c5034 (vtable and constructor not identified yet; 0x71012c384c
// loads a vptr from the same object, so the real class is polymorphic).
class Unk_71012C5034 {
public:
    // Slots 0 / 1 are assumed to be the destructors; slots 2..6 are called by the functions below (names unknown).
    virtual ~Unk_71012C5034();
    // Called with a part name (Unk68::sub_710104DD20 passes "BaseEquip_Quiver").
    virtual bool m2(const sead::SafeString& name);
    virtual bool m3();
    virtual void m4(void* arg);
    virtual void m5(void* arg);
    virtual void m6();

    // 0x71012c5034 (declared only)
    void sub_71012C5034(s32 value);
    // 0x71012c384c (placeholder name): _c = m2(name), _d = !_c.
    void sub_71012C384C(const sead::SafeString& name);
    // 0x71012c3888 / 0x71012c38f8 (placeholder names): if _d is set, first _c = m3() (clearing _d); then m4 / m5
    // while _c is set.
    void sub_71012C3888(void* arg);
    void sub_71012C38F8(void* arg);
    // 0x71012c3968 (placeholder name): m6(), then clears _c and _d.
    void sub_71012C3968();

    u8 _8[4];
    bool _c;
    bool _d;
    s32 _10;
};

// Placeholder name (vtable 0x7102502138, a sead singleton of size 0xfa8 created by 0x710103af1c and
// initialised from Sound::init (0x710103b1d4); instance pointer at 0x71026108e0, GOT 0x25924b0). Part of the
// sound system (it forwards small requests to a sub-object at +0x68, reads a map-static byml and keeps
// 0x168-byte records). Only what the callers use is declared so far.
class Unk_7102502138 {
    SEAD_SINGLETON_DISPOSER(Unk_7102502138)
    Unk_7102502138();

public:
    virtual ~Unk_7102502138();

    // 0x710103b41c (declared only): forwards `flag` to the sub-object at +0x68 (0x710104d398). Called with false by
    // SetPlayerDrawingSword::oneShot_.
    void sub_710103B41C(bool flag);
    // 0x710103b430 (lane4 s49): forwards `flag` to the sub-object at +0x68 (0x710104d620). Called with false by
    // Player::sub_710088A854.
    void sub_710103B430(bool flag);
    // 0x710103b414 / 0x710103b428 (declared only): forward to the sub-object at +0x68 (0x710104d068 / 0x710104d3b0).
    void sub_710103B414(const sead::SafeString& name);
    void sub_710103B428(const sead::SafeString& name, xlink::XLink* xlink);

    void sub_710103B43C(const sead::SafeString& name);
    void sub_710103B444(bool flag);
    void sub_710103B450(const sead::SafeString& name);
    void sub_710103B458(const sead::SafeString& name);
    void sub_710103B460(const sead::SafeString& name);
    void sub_710103B468(bool flag);
    void sub_710103B47C(bool flag);
    // 0x710103b474 (8 B): forwards `value` to the sub-object at +0x68 (Unk68::sub_710104DD7C).
    void sub_710103B474(s32 value);

    // 0x710103b1d4 (CSV Sound::init part): creates the sub-object (once).
    void init(sead::Heap* heap);
    // 0x710103b234 (declared only): placeholder name.
    void sub_710103B234();
    // 0x710103b33c / 0x710103b384 / 0x710103b3cc: forward to the sub-object (0x710104df54 / 0x710104e004 /
    // 0x710104e0a0) under the critical section.
    void sub_710103B33C(f32 value);
    void sub_710103B384(f32 value);
    void sub_710103B3CC(void* arg);

    // Placeholder (the sub-object at +0x68, 0x578 bytes; mostly declaration only).
    struct Unk68 {
        Unk68();
        virtual ~Unk68();
        // 0x710104bcbc
        void init(sead::Heap* heap);
        // 0x710104bef0 / 0x710104df54 / 0x710104e004 / 0x710104e0a0 (declared only)
        // 0x710104bef0: applies the dirty parts (_56c bit 2: 0x710104bf44, bit 3: 0x710104c648) and clears the bits.
        void sub_710104BEF0();
        // 0x710104bf44 / 0x710104c648 (declared only; 1796 / 2592 B).
        void sub_710104BF44();
        void sub_710104C648();
        void sub_710104DF54(f32 value);
        void sub_710104E004(f32 value);
        void sub_710104E0A0(void* arg);

        // 0x710104d398: `_15c = flag` and bit 3 of the dirty flags `_56c`.
        void sub_710104D398(bool flag);
        // 0x710104d620: `_bc = flag` and bit 3 of the dirty flags `_56c`.
        void sub_710104D620(bool flag);
        // 0x710104d068 / 0x710104d3b0 (declared only).
        void sub_710104D068(const sead::SafeString& name);
        // 0x710104d204 (placeholder name): whether `name` is "None", "No_Sound", "Dummy" or `current`.
        bool sub_710104D204(const sead::SafeString& name, const sead::SafeString& current) const;
        void sub_710104D3B0(const sead::SafeString& name, xlink::XLink* xlink);

        void sub_710104D638(const sead::SafeString& name);
        void sub_710104D834(bool flag);
        void sub_710104D84C(const sead::SafeString& name);
        void sub_710104D9E8(const sead::SafeString& name);
        void sub_710104DB84(const sead::SafeString& name);
        // 0x710104dd20 / 0x710104dd88 (placeholder names): set / clear bit 0 (bit 1) of _56c and pass
        // "BaseEquip_Quiver" to _480 ("BaseEquip_Belt" to _520, then mark bits 2 and 3 dirty).
        void sub_710104DD20(bool flag);
        void sub_710104DD88(bool flag);
        // 0x710104dd7c (12 B): `_568 = value`, then forwards `value` to the object at +0x480 (Unk_71012C5034::sub_71012C5034).
        void sub_710104DD7C(s32 value);

        // Placeholder: the objects at 0x528..0x558 (only their part object at 0x98 is read).
        struct Part {
            u8 _0[0x98];
            Unk_71012C5034* _98;
        };

        // The shield names searched by sub_710104D3B0 (count at +0x8, array at +0x10).
        /* 0x08 */ sead::PtrArray<sead::SafeString> mShieldNames;
        u8 _18[0x28 - 0x18];
        // The shield part name (same 0x94-byte string layout as the five below).
        /* 0x28 */ sead::FixedSafeString<0x78> _28;
        /* 0xb8 */ u8 _28_pad[4];
        /* 0xbc */ bool _bc;
        /* 0xc0 */ Unk_71012C5034* _c0;
        // The part names: the sead string is followed by the group's skip flag and part object. The
        // original's strings are 0x94 bytes (4-byte aligned, a 0x80 buffer) instead of our 0x98, so the
        // 0x78 buffer plus the explicit pad keeps every later member at its real offset.
        /* 0xc8 */ sead::FixedSafeString<0x78> _c8;
        /* 0x158 */ u8 _c8_pad[4];
        /* 0x15c */ bool _15c;
        /* 0x160 */ Unk_71012C5034* _160;
        /* 0x168 */ sead::FixedSafeString<0x78> _168;
        /* 0x1f8 */ u8 _168_pad[4];
        /* 0x1fc */ bool _1fc;
        /* 0x200 */ Unk_71012C5034* _200;
        /* 0x208 */ sead::FixedSafeString<0x78> _208;
        /* 0x298 */ u8 _208_pad[4];
        /* 0x29c */ bool _29c;
        /* 0x2a0 */ Unk_71012C5034* _2a0;
        /* 0x2a8 */ sead::FixedSafeString<0x78> _2a8;
        /* 0x338 */ u8 _2a8_pad[4];
        /* 0x33c */ bool _33c;
        /* 0x340 */ Unk_71012C5034* _340;
        /* 0x348 */ sead::FixedSafeString<0x78> _348;
        /* 0x3d8 */ u8 _348_pad[4];
        /* 0x3dc */ bool _3dc;
        /* 0x3e0 */ Unk_71012C5034* _3e0;
        u8 _3e8[0x480 - 0x3e8];
        /* 0x480 */ Unk_71012C5034* _480;
        u8 _488[0x520 - 0x488];
        /* 0x520 */ Unk_71012C5034* _520;
        /* 0x528 */ Part* _528;
        /* 0x530 */ Part* _530;
        /* 0x538 */ Part* _538;
        /* 0x540 */ Part* _540;
        /* 0x548 */ Part* _548;
        /* 0x550 */ Part* _550;
        /* 0x558 */ Part* _558;
        u8 _560[0x568 - 0x560];
        /* 0x568 */ s32 _568;
        /* 0x56c */ u16 _56c;
        u8 _56e[0x578 - 0x56e];
    };

    // Placeholder (an entry of the list at +0x70; 0x68 bytes, declaration only).
    struct Unk70Entry {
        Unk70Entry();
        // 0x710103b5c8 (declared only)
        bool sub_710103B5C8(void* user, bool a);

        f32 _0 = 1.0f;
        u32 _4 = 0;
        f32 _8 = 1.0f;
        u32 _c = 0;
        f32 _10 = 0.4f;
        u32 _14;
        sead::FixedSafeString<0x30> _18;
        bool _60 = false;
        u8 _61[7];
    };

    // 0x710103b488: takes an entry from the fixed list (null when full).
    Unk70Entry* sub_710103B488();
    // 0x710103b4f8: the name of the first entry whose _60 flag is set, or null.
    const sead::SafeString* sub_710103B4F8();

private:
    /* 0x28 */ sead::CriticalSection mCS;
    /* 0x68 */ Unk68* _68 = nullptr;
    /* 0x70 */ sead::FixedObjList<Unk70Entry, 32> mList;
    /* 0xfa0 */ bool mInitialized = false;
};
KSYS_CHECK_SIZE_NX150(Unk_7102502138, 0xfa8);

// 0x710104ddf8 (unnamed): whether `name` is a usable sound name, i.e. none of the three empty-name
// placeholders "Dummy", "None" and "No_Sound". The same strings the entry lookup at 0x710104d204 uses.
bool sub_710104DDF8(const sead::SafeString& name);

}  // namespace ksys::snd
