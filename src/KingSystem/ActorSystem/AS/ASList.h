#pragma once
#include <container/seadBuffer.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Resource/resResourceASSetting.h"
namespace ksys::res {
class ModelList;
}

namespace ksys::as {
class Context;
class Element;
}  // namespace ksys::as

namespace ksys::as {
class ASList {
public:
    // Placeholder: event query filled by the handlers passed to x() (0x7101259c78 copies a 0x20-byte AS
    // event entry: the name, then two 32-bit values). Callers pass nullptr when they only test for the event.
    struct Unk4 {
        sead::SafeString name;
        f32 _10;
        f32 _14;
    };
    static_assert(sizeof(Unk4) == 0x18);

    // 0x7101259d04 and callers 0x7101160120 / 0x7101235830: a sixteen-entry event result.
    struct EventQueryResults {
        sead::SafeArray<Unk4, 16> events;
        s32 count;
    };
    static_assert(sizeof(EventQueryResults) == 0x188);

    // Placeholder: 0x98-byte entry of a slot's bank buffer (the member functions passed to the
    // x/x_3/x_5/x_7 helpers below live at 0x71011612e8-0x7101163b24).
    struct Unk2 {
        // inline: their out-of-line copies are emitted in the callers' TUs
        bool sub_710002E82C() { return _18 != nullptr; }
        bool sub_7100023B58() { return _41 >> 3 & 1; }
        // 0x710042bbec: sets bit 8 of the halfword at 0x40.
        void sub_710042BBEC();
        // 0x71011623dc: copies frame state when both slots use the same resource.
        void sub_71011623DC(Unk2* other);
        // 0x7101162e88: copies matching slot state and links the two entries.
        void sub_7101162E88(Unk2* other, bool a1);
        // 0x7101161ee0: applies the element's partial-bone value (declaration only).
        void sub_7101161EE0(f32 value, Element* element, bool a1);

        // 0x7101161cd8 (declaration only): the context's string (empty if there is no element).
        const sead::SafeString* sub_7101161CD8();
        // used with x_7
        bool sub_7101162F2C();
        bool sub_7101162FE8();
        bool sub_7101162F7C(f32 value);
        f32 sub_7101163354(bool a1);
        void sub_71011635C0();
        int sub_710116360C(f32* out);
        int sub_710116367C();
        void sub_71011637D8();
        void sub_7101163AD4(f32 value, int key);
        void sub_7101163960(s32 start, s32 middle, s32 end, s32 index,
                           const res::ASSetting::BoneParams* params);
        bool sub_710116392C();
        void sub_710116173C();
        bool sub_7101163940();
        bool sub_7101163950();
        bool sub_7101163AF4();
        // used with x
        bool sub_71011637EC(Unk4* query, int a2, bool a3);
        bool sub_710116383C(Unk4* query, int a2, bool a3);
        bool sub_710116388C(Unk4* query, int a2, bool a3);
        bool sub_71011638DC(Unk4* query, int a2, bool a3);
        bool sub_7101163818(EventQueryResults* query, int type, bool a3);
        bool sub_7101163868(EventQueryResults* query, int type, bool a3);
        bool sub_71011638B8(EventQueryResults* query, int type, bool a3);
        bool sub_7101163908(EventQueryResults* query, int type, bool a3);
        // 0x7101162254
        bool sub_7101162254(bool a1);
        // 0x7101161cf8 / 0x71011633c0: used by ASList::sub_710115F1D8 / sub_710115F158.
        void sub_7101161CF8(bool a1, f32 a2);
        void sub_71011633C0(Unk2* other);
        // 0x71011634c0: updates the element position, then evaluates its event state.
        void sub_71011634C0(f32 value);
        // used by Unk1::sub_7101164F3C
        void sub_7101162DE4(sead::Vector3f* a1, sead::Vector3f* a2, const gsys::BoneAccessKey* key);
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

        /* 0x00 */ Context* _0;
        /* 0x08 */ u8 _8[0x10 - 0x8];
        /* 0x10 */ f32 _10;
        /* 0x18 */ Element* _18;
        /* 0x20 */ void* _20;
        /* 0x28 */ void* _28;
        /* 0x30 */ u8 _30[0x40 - 0x30];
        /* 0x40 */ union {
            u16 mFlags;
            struct {
                u8 _40;
                u8 _41;
            };
        };
        /* 0x42 */ u8 _42;
        /* 0x43 */ u8 _43;
        /* 0x44 */ u8 _44[0x48 - 0x44];
        /* 0x48 */ Unk2* _48;
        struct BoneWeightRange {
            s16 start;
            s16 middle;
            s16 end;
            const res::ASSetting::BoneParams* params;
        };
        static_assert(sizeof(BoneWeightRange) == 0x10);
        /* 0x50 */ sead::SafeArray<BoneWeightRange, 3> mBoneWeightRanges;
        /* 0x80 */ u8 _80[0x98 - 0x80];
    };
    static_assert(sizeof(Unk2) == 0x98);

    // Placeholder: 0x50-byte slot.
    struct Unk1 {
        // 0x7101164f3c: calls Unk2::sub_7101162DE4 on every entry of _20 (unless the bit `key` selects is
        // clear or _4d is set).
        void sub_7101164F3C(sead::Vector3f* a1, sead::Vector3f* a2, const gsys::BoneAccessKey* key);
        // 0x7101164900: per-slot update from the model list (partial count of slot `idx`).
        void sub_7101164900(const res::ModelList* model_list, int idx, act::Actor* actor);

        // 0x7101165008 (declaration only; lane4 s23): partial bone `key` of the slot, `mode` 3 (the root) or 0,
        // `a3` selects the variant of the two helpers 0x7100bff95c / 0x7100bff8e4.
        void sub_7101165008(const gsys::BoneAccessKey& key, int mode, bool a3);
        // 0x7101164e38 (declaration only): sets (true) / resets (false) the flag at 0x4d (or calls 0x7100bff4cc).
        void sub_7101164E38(bool a1);
        // 0x7101164ff8 (declaration only): the slot's partial bone setup.
        void sub_7101164FF8();

        // 0x71011650b8: bit `bit` of row `row` of the partial-bone mask (true if there is no mask).
        bool sub_71011650B8(int row, int bit) const;
        bool sub_7101164C24(const gsys::BoneAccessKey& key) const;
        // 0x7101165278: highest weighted element query; optional returned index.
        Unk2* sub_7101165278(s32* index);
        // 0x710116532c: first element query returning a nonnegative index.
        Unk2* sub_710116532C(s32* index);
        bool sub_71011653A4() const;
        bool sub_71011653B4() const;
        bool sub_71011653C4() const;

        struct BitRow {
            u32 words[32];
        };

        u8 _0[0x20];
        sead::Buffer<Unk2> _20;
        void* _30;
        sead::Buffer<BitRow> _38;
        f32 _48;
        u8 _4c;
        bool _4d;
        u8 _4e[0x50 - 0x4e];
    };

    // Placeholder: 8-byte parameter value; depending on the parameter kind it holds a value or a
    // pointer (the destructor deletes some kinds).
    union Unk3 {
        f32 _f32;
        s32 _s32;
        u64* _u64_ptr;
        sead::BufferedSafeString* _str_ptr;
        sead::Vector3f* _vec3_ptr;
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
    // 0x710115f5c0: updates a slot/bank entry and all subsequent entries linked to it.
    void sub_710115F5C0(f32 value, int slot, int bank);
    // 0x710115f228 (declaration only; MiniGolemRoot::calc_ passes a 0..1 ratio).
    void sub_710115F228(f32 value);
    // 0x710115f2ec: changes the entry weight and updates the slot.
    void sub_710115F2EC(s32 slot, s32 bank, f32 value);
    f32 sub_710115CAFC(const sead::SafeString& bone_name);
    bool sub_710115F0BC(int slot, int bank, f32 value);
    void sub_710115F10C(int slot, int bank);
    void sub_710115F6F4(int key, int slot, int bank, f32 value);
    bool sub_710115F024(const sead::Vector3f& value, int a2);
    const sead::Vector3f& sub_710115F078();
    // 0x710115f3f0: queries normalized playback position.
    f32 sub_710115F3F0(int slot, int bank, bool a1);
    // 0x710115ea64: copies one of five string parameter values.
    bool sub_710115EA64(int kind);
    bool sub_710115EECC(int kind, s32 value, int a3);
    // 0x710115fbc8 (declaration only): like x() but over every slot / bank entry.
    bool sub_710115FBC8(int a1, Unk4* query, bool (Unk2::*fn)(Unk4*, int, bool), bool a4);
    f32 x_5(int slot, int bank, f32 (Unk2::*fn)());
    bool x_7(int slot, int bank, bool (Unk2::*fn)());
    // All 368 callers pass 0 in w2: the second int parameter is unused here (its position before or after
    // `value` cannot be told from the binary; the other helpers take two ints first).
    bool x_6(int kind, int a2, f32 value);
    // 0x710115efd0 (declaration only): stores `value` (clamped to 1 if `clamp`) in the table entry of
    // `kind`; false if the kind is unused. The fourth parameter (w3) is unused (as in x_2).
    bool sub_710115EFD0(int kind, bool clamp, bool a3, f32 value);
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
    // 0x710115baf8: sets the bone name _18 and looks it up in the model (_14; invalid if empty).
    void sub_710115BAF8(const sead::SafeString& bone_name);
    // 0x710115ce44 / 0x710115d0ac: push / pop a bone name (the first push saves _18 in _40).
    void sub_710115CE44(const sead::SafeString& bone_name);
    void sub_710115D0AC();
    // 0x710115b140 (declaration only; lane4 s23): starts the animation `name` on the entry (slot, bank) of
    // `slot2` / `bank2` (placeholder parameter names; GiantWeaponGrabAS passes (name, slot, 0, 0, 0)).
    void sub_710115B140(const sead::SafeString& name, int slot, int slot2, int bank, int bank2);
    // 0x710115f444 (declaration only): calls `fn` on the entry (slot, bank) (like x_3, without a value).
    void sub_710115F444(int slot, int bank, void (Unk2::*fn)());
    // 0x710115c9e0 (declaration only; lane4 s23): `slot`'s partial bone setup (ModelList::isParticalEnable(slot),
    // then the slot's helper 0x7101164ff8).
    void sub_710115C9E0(int slot);
    // 0x710115b01c: Unk2::sub_7101162254(a3) on the entry of `slot` / `bank` (false if none).
    bool sub_710115B01C(int slot, int bank, bool a3);
    // 0x710115c11c: clears bit 1 of _163 (returns whether it was set) and updates every slot.
    bool sub_710115C11C();
    // 0x710115bed4: per-slot update (placeholder; returns a slot index). Not decompiled yet (calls
    // unnamed Unk1 helpers 0x71011653a4 / 0x7101164ff8 / 0x7101165008 / 0x7101164e38).
    s32 sub_710115BED4(bool a1);
    // 0x710115bc28: looks up the define `name` (sub_710115AABC) and applies it with `value`
    // (placeholder; returns a slot index or 0). Not decompiled yet.
    s32 sub_710115BC28(const sead::SafeString& name, f32 value);
    // 0x710115cd0c (declared only; placeholder name): IsMorphEndASPlay::leave_, SetTargetFrameMtx::leave_.
    void sub_710115CD0C();
    // 0x710115f1d8: Unk2::sub_7101161CF8(true, value) on the entry of `slot` / `bank`.
    void sub_710115F1D8(int slot, int bank, f32 value);
    // 0x710115f158: Unk2::sub_71011633C0 on this list's entry (slot, bank) with `other`'s entry
    // (other_slot, other_bank).
    void sub_710115F158(ASList* other, int slot, int other_slot, int bank, int other_bank);
    // 0x710115ec5c: the integer parameter `kind` (_e0[_f0[kind]]), 0 if unset; `a2` is unused.
    int sub_710115EC5C(int kind, int a2);
    // 0x710115ec98: the float parameter `kind`, or `fn`'s result when given; `a4` is unused.
    f32 sub_710115EC98(int kind, f32 (ASList::*fn)(), int a4);
    // Fallback getters of the float parameters 0x13 / 0x14 / 0x15 / 0x16 / 0x1b (declaration only).
    // 0x7101160ed4 (declaration only): the owner's model-side object gets a flag and a back pointer to this list.
    void sub_7101160ED4();
    f32 sub_710115F740();
    f32 sub_710115F820();
    f32 sub_710115F8A0();
    f32 sub_710115F98C();
    f32 sub_710115FA78();
    // 0x710131d504 (in the RandomSelector TU): a random value in [0, 1) (ignores the list).
    f32 sub_710131D504();
    // 0x710115ecf4: the string parameter `kind` (_e0[_f0[kind]]), or "" if unset; `a2` is unused.
    const char* sub_710115ECF4(int kind, int a2);
    // 0x710115ee14: bit `bit` of the flags parameter (answered by the owner for bits 0 / 0x19 / 6).
    bool sub_710115EE14(int bit);
    // 0x710115ed5c: getter counterpart of x_2: bit `bit` of the flags parameter (_f0[0x42]), with
    // bits 0 / 0x19 / 6 answered by the owner (basic signal / remains signal / LodState flag 1).
    bool sub_710115ED5C(int a1, int bit);

    // inline-only in the original; name is a guess. Evidence: loop bounds of CapturedActFreeze /
    // CapturedActElectricParalyisis calc_ / leave_: the number of banks of slot 0.
    s32 getSlot0BankCount() const { return mSlots.size() > 0 ? mSlots[0]._20.size() : 0; }

    Unk2* getEntry(int slot, int bank) {
        if (slot >= mSlots.size())
            return nullptr;
        auto& entries = mSlots[slot]._20;
        if (bank >= entries.size())
            return nullptr;
        return &entries[bank];
    }

    // vtable 0x710250ff98 (6 virtual functions, the destructor 0x7101159ca0 last) — not modelled
    /* 0x000 */ u8 _0[0x8];
    /* 0x008 */ gsys::Model* _8;
    /* 0x010 */ u8 _10[0x13 - 0x10];
    /* 0x013 */ u8 _13;  // push depth of the bone name (sub_710115CE44 / sub_710115D0AC)
    /* 0x014 */ gsys::BoneAccessKey _14;  // bone named _18 (sub_710115BAF8)
    /* 0x018 */ sead::FixedSafeString<20> _18;
    /* 0x040 */ sead::FixedSafeString<20> _40;  // saved _18 while pushed
    /* 0x068 */ sead::Vector3f _68;
    /* 0x074 */ sead::Vector3f _74;
    /* 0x080 */ sead::Matrix34f _80;  // read with _14 (Remains::sub_71002CA3EC)
    /* 0x0b0 */ u8 _b0[0xb8 - 0xb0];
    /* 0x0b8 */ sead::Buffer<Unk1> mSlots;
    /* 0x0c8 */ sead::Buffer<Unk2*> _c8;
    /* 0x0d8 */ act::Actor* _d8;  // owner
    /* 0x0e0 */ sead::Buffer<Unk3> _e0;
    /* 0x0f0 */ sead::SafeArray<s8, 0x43> _f0;
    /* 0x133 */ u8 _133[0x163 - 0x133];
    /* 0x163 */ u8 _163;
};

// 0x7101259c78 (declaration only): finds the first event of `type` whose mask has a bit of `mask` in the
// context's event ring; copies its name / values into `query` (if given).
bool sub_7101259C78(Context* ctx, ASList::Unk4* query, int type, u16 mask, ASList::Unk2* entry);
bool sub_7101259D04(Context* ctx, ASList::EventQueryResults* query, u32 type, u16 mask);

// 0x7102620bb0 (GOT 0x25a15c8): the ASList that Actor::mASList is compared with before use (Actor::m120 /
// m121, job0_2, job2_1, ...): a placeholder / null list. Name is a guess.
extern ASList sNullASListMaybe;

}  // namespace ksys::as
