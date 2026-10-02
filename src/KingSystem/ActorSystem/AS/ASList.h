#pragma once
#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actActor.h"
namespace ksys::as {
class ASList {
public:
    // Placeholder: event query filled by the handlers passed to x() (0x7101259c78 copies a 0x20-byte AS
    // event entry: the name, then two 32-bit values). Callers pass nullptr when they only test for the event.
    struct Unk4 {
        sead::SafeString name;
        f32 _10;
        u32 _14;
    };

    // Placeholder: a pair of indices read by the anim-driven movement accumulators below (both -1 =
    // none).
    struct Unk5 {
        s16 _0;
        s16 _2;
    };

    // Placeholder: 0x98-byte entry of a slot's bank buffer (the member functions passed to the
    // x/x_3/x_5/x_7 helpers below live at 0x71011612e8-0x7101163b24).
    struct Unk2 {
        // inline: their out-of-line copies are emitted in the callers' TUs
        bool sub_710002E82C() { return _18 != nullptr; }
        bool sub_7100023B58() { return _41 >> 3 & 1; }

        // used with x_7
        bool sub_7101162F2C();
        bool sub_7101162FE8();
        bool sub_710116392C();
        bool sub_7101163940();
        bool sub_7101163950();
        bool sub_7101163AF4();
        // used with x
        bool sub_71011637EC(Unk4* query, int a2, bool a3);
        bool sub_710116383C(Unk4* query, int a2, bool a3);
        bool sub_710116388C(Unk4* query, int a2, bool a3);
        bool sub_71011638DC(Unk4* query, int a2, bool a3);
        // used by Unk1::sub_7101164F3C
        void sub_7101162DE4(sead::Vector3f* a1, sead::Vector3f* a2, const Unk5* idx);
        // used with x_3
        void sub_7101163044(f32 value);
        void sub_7101163100(f32 value);
        void sub_71011631BC(f32 value);
        void sub_71011631DC(f32 value);
        void sub_7101163298(f32 value);
        // used with x_5
        f32 sub_71011630A4();
        f32 sub_7101163160();
        f32 sub_71011631D0();
        f32 sub_710116323C();
        f32 sub_71011632F8();
        f32 sub_7101163564();

        /* 0x00 */ void* _0;
        /* 0x08 */ u8 _8[0x10 - 0x8];
        /* 0x10 */ f32 _10;
        /* 0x18 */ void* _18;
        /* 0x20 */ void* _20;
        /* 0x28 */ void* _28;
        /* 0x30 */ u8 _30[0x41 - 0x30];
        /* 0x41 */ u8 _41;
        /* 0x42 */ u8 _42;
        /* 0x43 */ u8 _43;
        /* 0x44 */ u8 _44[0x98 - 0x44];
    };

    // Placeholder: 0x50-byte slot.
    struct Unk1 {
        // 0x7101164f3c: calls Unk2::sub_7101162DE4 on every entry of _20 (unless the bit `idx` selects is
        // clear or _4d is set).
        void sub_7101164F3C(sead::Vector3f* a1, sead::Vector3f* a2, const Unk5* idx);

        u8 _0[0x20];
        sead::Buffer<Unk2> _20;
        u8 _30[0x50 - 0x30];
    };

    // Placeholder: 8-byte parameter value; depending on the parameter kind it holds a value or a
    // pointer (the destructor deletes some kinds).
    union Unk3 {
        f32 _f32;
        u64* _u64_ptr;
    };

    void startAnimationMaybe(f32 a2, f32 a3, const sead::SafeString& animation, int a5, int a6,
                             bool a7);
    bool goLimpFromHeadShotMaybe(u32 a1, const sead::SafeString& a2, u32 a3);  // x_8
    // All 141 callers pass a fourth argument in w4 (129 x 0, 12 x 1) that is unused here; its type (bool or
    // int) cannot be told from the binary.
    bool x_2(int a1, int bit, bool on, bool a4);
    // 0x000000710115c458
    const sead::SafeString& x_1(u32 slot, u32 seq_bank);
    // 0x000000710115c4d4
    bool x_4(u32 slot, u32 seq_bank);

    // Call `fn` on the entry of slot `slot`, bank `bank` (if it exists).
    // `query` is null in 356 of the 432 calls in the original.
    bool x(int a1, Unk4* query, int slot, int bank, bool (Unk2::*fn)(Unk4*, int, bool), bool a6);
    void x_3(int slot, int bank, void (Unk2::*fn)(f32), f32 value);
    f32 x_5(int slot, int bank, f32 (Unk2::*fn)());
    bool x_7(int slot, int bank, bool (Unk2::*fn)());
    // All 368 callers pass 0 in w2: the second int parameter is unused here (its position before or after
    // `value` cannot be told from the binary; the other helpers take two ints first).
    bool x_6(int kind, int a2, f32 value);
    // 0x710115aabc: looks up the AS define `name` (res::ASList::findASDefine) and returns its entry
    // (null if none); outputs the define's name and two values. Return type and outputs are
    // placeholders.
    void* sub_710115AABC(const sead::SafeString& name, sead::SafeString* out_name, bool* out_a3,
                         void** out_a4, bool a5);
    // 0x710115aa68: whether sub_710115AABC finds `name` (a5 = true).
    bool sub_710115AA68(const sead::SafeString& name);
    // 0x710115d2d4: the anim-driven translation of this frame (_68), accumulated over all slots on the
    // first call (bit 0 of _163; _74 is accumulated alongside). ~36 anim-driven move actions use it.
    const sead::Vector3f& sub_710115D2D4();
    // 0x710115d3b8: the same, returning _74 (~40 callers).
    const sead::Vector3f& sub_710115D3B8();

    Unk2* getEntry(int slot, int bank) {
        if (slot >= mSlots.size())
            return nullptr;
        auto& entries = mSlots[slot]._20;
        if (bank >= entries.size())
            return nullptr;
        return &entries[bank];
    }

    /* 0x000 */ u8 _0[0x14];
    /* 0x014 */ Unk5 _14;
    /* 0x018 */ u8 _18[0x68 - 0x18];
    /* 0x068 */ sead::Vector3f _68;
    /* 0x074 */ sead::Vector3f _74;
    /* 0x080 */ u8 _80[0xb8 - 0x80];
    /* 0x0b8 */ sead::Buffer<Unk1> mSlots;
    /* 0x0c8 */ sead::Buffer<Unk2*> _c8;
    /* 0x0d8 */ u8 _d8[0xe0 - 0xd8];
    /* 0x0e0 */ sead::Buffer<Unk3> _e0;
    /* 0x0f0 */ sead::SafeArray<s8, 0x43> _f0;
    /* 0x133 */ u8 _133[0x163 - 0x133];
    /* 0x163 */ u8 _163;
};

}  // namespace ksys::as
