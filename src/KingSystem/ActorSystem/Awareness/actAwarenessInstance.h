#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadObjArray.h>
#include <container/seadSafeArray.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

class Unk_71023e2708;

namespace ksys::act {

class Actor;
class Unk_71024dc858;
struct Unk_7100d78e50;

// Placeholder name (vtable 0x71024dce08): base class of the four sensor objects an
// AwarenessInstance owns (created in 0x7100d7b974; derived vtables e.g. 0x71024dcea8).
// TODO: incomplete.
class Unk_71024dce08 {
    SEAD_RTTI_BASE(Unk_71024dce08)
public:
    // D1 0x7100d7f7b4, D0 0x7100d7f848 (vtable slots 2/3 after the RTTI functions 0x7100d8018c /
    // 0x7100d801fc).
    virtual ~Unk_71024dce08();

    // Slots 4-17 (base implementations 0x7100d7f71c-0x7100d7f750 and 0x7100d80038). Names and
    // signatures are placeholders except m16: 4-6, 12 and 14 are pure; the base m7 / m11 return true,
    // m10 returns 0, m8 / m9 / m13 are empty.
    // The requests are Unk_71023e2708 objects (actAwarenessRequest.h; each sensor kind takes its own derived type).
    virtual bool m4(Unk_71023e2708* request) = 0;
    virtual bool m5(Unk_71023e2708* request) = 0;
    virtual bool m6(Unk_71023e2708* request) = 0;
    virtual bool m7();
    virtual void m8();
    virtual void m9();
    virtual bool m10();
    virtual bool m11();
    virtual void m12() = 0;
    virtual void m13();
    // 0x7100d7c494 multiplies its result with _4c (the interest level of the sensor).
    virtual f32 m14() = 0;
    virtual void m15();
    // 0x7100d7f748 (base: null); 0x7100d81dc8 (vtable 0x71024dcea8): a flag byte at +0x68.
    // EnemyNormal::m41 clears bit 0 of it.
    virtual sead::BitFlag8* m16();
    virtual void m17();

    /* 0x08 */ sead::ObjArray<Unk_7100d78e50> _8;
    /* 0x28 */ u8 _28[0x3c - 0x28];
    /* 0x3c */ u32 _3c;
    /* 0x40 */ u8 _40[0x48 - 0x40];
    /* 0x48 */ s32 _48;  // cleared by SimpleWildlifeRoot::m37
    /* 0x4c */ f32 _4c;
    /* 0x50 */ bool _50;  // active (AwarenessInstance::sub_7100D7E9BC / sub_7100D7EAE4)
};

// Placeholder name (vtable 0x71024dc978, RTTI static 0x71025af288): abstract base of the awareness
// entries (Unk_71024dc858, the first member of the awareness array elements Unk_7100d78e50); the
// filters get them through this type.
// 17 virtual slots: RTTI, dtor (empty), 4-10 / 14-16 pure, 11 / 12 empty, 13.
// TODO: incomplete.
class Unk_71024dc978 {
    SEAD_RTTI_BASE(Unk_71024dc978)
public:
    // The original D1 (0x7100d78244) keeps the vtable store that a defaulted dtor drops; written as
    // `{ ; }` like upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229).
    virtual ~Unk_71024dc978() { ; }

    // Slots 4-10 (implemented by Unk_71024dc858 at 0x7100d77368-0x7100d773e0; names unknown).
    virtual f32 m4(int idx) = 0;
    virtual bool m5(int bit) const = 0;
    virtual sead::BitFlag16* m6() = 0;
    virtual bool m7(sead::Vector3f* pos) = 0;  // the linked actor's previous position
    virtual bool m8(sead::Vector3f* vel) = 0;  // the linked actor's velocity
    virtual void m9(int idx, f32 value) = 0;
    virtual void m10(int bit, bool on) = 0;  // sets / clears a bit of the u16 at +0x38
    // Slots 11-13 are empty / return -1 (0x7100d7825c, 0x7100d78260, 0x7100d78264); 14-18 are pure.
    // Names and the parameter types of m11 / m12 / m14 / m16 are placeholders (see Unk_71024dc858).
    virtual void m11() {}
    virtual void m12(void*) {}
    virtual f32 m13() { return -1.0f; }
    virtual bool m14(Unk_71024dc978* other) = 0;
    virtual void m15() = 0;
    virtual bool m16(Unk_71024dc978* other) = 0;
    virtual f32 m17(int idx) = 0;
    virtual void m18() = 0;
};

// Placeholder name (vtable 0x71024dc858, RTTI static 0x71025af278, ctors 0x7100d771cc / 0x7100d77254
// (with an actor), D1 0x7100d772d4, size 0x58): an awareness target entry. The ctors initialise up to
// 0x52 and the embedding objects place the next member at +0x58 (Unk_71024dc900: entry at +0x18,
// actor at +0x70; the HornUse awareness object 0x710235f078: entry at +0x28, member at +0x80).
// Must not be `final`: filters call its virtuals through DynamicCast results.
// TODO: incomplete (m11 / m12 / m14 are declared only).
class Unk_71024dc858 : public Unk_71024dc978 {
    SEAD_RTTI_OVERRIDE(Unk_71024dc858, Unk_71024dc978)
public:
    Unk_71024dc858();
    // 0x7100d77254: also links `actor`.
    explicit Unk_71024dc858(Actor* actor);
    ~Unk_71024dc858() override;

    f32 m4(int idx) override;
    bool m5(int bit) const override;
    sead::BitFlag16* m6() override;
    bool m7(sead::Vector3f* pos) override;
    bool m8(sead::Vector3f* vel) override;
    void m9(int idx, f32 value) override;
    void m10(int bit, bool on) override;

    // Slots 11-18. 0x7100d7774c: unless inactive (_50) or the world manager's (GOT 0x7102590c10)
    // byte 0x128 has bits 4 / 1 set: clears _1c/_20/_3c/_48, calls m10(1, 0) / m10(2, 0)... (not
    // decompiled). 0x7100d77854: takes a pointer (not decompiled). 0x7100d77530: copies an entry
    // (`other` is a Unk_71024dc858; returns whether it was one; not decompiled).
    void m11() override;
    void m12(void* arg) override;
    f32 m13() override { return _4c; }
    bool m14(Unk_71024dc978* other) override;
    // 0x7100d77230: resets the entry values (AITerror users call it devirtualised).
    void m15() override;
    // 0x7100d776b0: DynamicCast<Unk_71024dc858>(other) && mLink == other->mLink.
    bool m16(Unk_71024dc978* other) override;
    f32 m17(int idx) override { return _18[idx]; }
    void m18() override {}

    // 0x7100d77518 (used by AITerror::x)
    void sub_7100D77518(int idx, f32 value);

    /* 0x08 */ BaseProcLink mLink;  // the target actor
    /* 0x18 */ sead::SafeArray<f32, 4> _18{{1.0, 0, 0, 1.0}};  // m4 / m9
    /* 0x28 */ sead::SafeArray<f32, 4> _28{{1.0, 1.0, 1.0, 1.0}};  // m4
    /* 0x38 */ sead::BitFlag16 _38;  // m5 / m6 / m10
    /* 0x3c */ u32 _3c = 0;
    /* 0x40 */ u32 _40 = 0;
    /* 0x44 */ u32 _44 = 0;
    /* 0x48 */ s32 _48 = 0;
    /* 0x4c */ f32 _4c = -1.0;
    /* 0x50 */ u8 _50 = 0;
    /* 0x51 */ u8 _51 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71024dc858, 0x58);

// Placeholder name (no vtable, inline ctor; named after 0x7100d78e50, which builds one on the stack
// and inserts a copy into an awareness array): an element of the awareness arrays
// (AwarenessInstance::_8, Unk_71024dce08::_8). Size 0xb0: the arrays' FreeList stride is 0xb0 and
// their buffer is capacity * (0xb0 + sizeof(T*)) = 0xb8 per element (allocBuffer 0x7100d78d44).
// The entry is a member, not a base: element construction calls the entry ctor and stores no
// other vtable, and element destruction (sead::ObjArray::clear / erase in 0x7100d78f4c and
// AwarenessInstance::sub_7100D7EAE4) calls Unk_71024dc858's D1 directly.
struct Unk_7100d78e50 {
    // inline-only in the original; name is a guess (the same sequence (Unk_71024dc858 ctor, a memcpy of the identity
    // matrix, three zero stores) opens the stack copies in 0x7100d78e50 and KeeseHangOnCeil::calc_ (x2)).
    Unk_7100d78e50() : _58(sead::Matrix34f::ident), _a0(0), _a4(0), _a8(0) {}

    /* 0x00 */ Unk_71024dc858 _0;
    /* 0x58 */ sead::Matrix34f _58;  // passed as a matrix by EnemyCalledAppear::calc_ (sub_71005D8DE8)
    /* 0x88 */ sead::Vector3f _88;
    /* 0x94 */ sead::Vector3f _94;
    /* 0xa0 */ s32 _a0;  // kind (e.g. 2 checked by BeeSwarmNormal::m47)
    /* 0xa4 */ f32 _a4;  // compared with StoneOctarockGuardNearTarget NoticeTerrorLevel
    /* 0xa8 */ f32 _a8;  // distance-like value compared by many AI functions (arrays sorted by it)
};
KSYS_CHECK_SIZE_NX150(Unk_7100d78e50, 0xb0);

class AwarenessInstance;
class AITerror;

// 0x7102600a38 (GOT 0x259bc58): bit i (0-3) disables the sensor `AwarenessInstance::_260[i]` in
// calcForEvent / sub_7100D7C494. Name is a guess (a debug switch: never set by the decompiled code).
extern sead::BitFlag8 sAwarenessDisabledSensorsMaybe;

// Placeholder name (vtable 0x71024dca28, RTTI functions 0x7100d78464 / 0x7100d784d4): abstract base
// of Unk_71024dc900; keeps a list of AITerror objects (_8, linked through AITerror::_a8).
// Slots 4-7 forward to the entry returned by m8 (0x7100d77fd8: `*m8()->m6()`; 0x7100d78530: entry
// slot 11; 0x7100d78388: updates every AITerror (0x7100d789e4) then entry slot 12; 0x7100d78004:
// entry slot 15). Signatures of m5-m7 are placeholders.
class Unk_71024dca28 {
    SEAD_RTTI_BASE(Unk_71024dca28)
public:
    Unk_71024dca28() = default;
    // 0x7100d782f8: unlinks every AITerror.
    virtual ~Unk_71024dca28();
    virtual u16 m4();
    virtual void m5();
    // The base forwards the actor argument to the awareness entry at slot12.
    virtual void m6(Actor* actor);
    virtual void m7();
    virtual Unk_71024dc978* m8() = 0;

    // 0x7100d783e4: activates `terror` and appends it to the list.
    void sub_7100D783E4(AITerror* terror);
    // 0x7100d78444: removes `terror` from the list (and deactivates it).
    void sub_7100D78444(AITerror* terror);

    /* 0x08 */ AITerror* _8 = nullptr;  // first AITerror
};

// Placeholder name (vtable 0x71024dc900; RTTI; created by 0x71011c57c0 (CSV Actor::x_27) with
// new(0x80)): Actor::_548. Contains an awareness entry at +0x18 (vtable 0x71024dc858, ctor
// 0x7100d77254 (entry, actor)), the actor at +0x70 and a u16 at +0x78; a second base at +0x10.
// Overrides slots 5, 6 and 8 of Unk_71024dca28.
// TODO: incomplete (only the virtual slot used by player actions is declared).
class Unk_71024dc900 : public Unk_71024dca28 {
    SEAD_RTTI_OVERRIDE(Unk_71024dc900, Unk_71024dca28)
public:
    ~Unk_71024dc900() override;
    void m5() override;
    void m6(Actor* actor) override;
    // 0x7100d77eac: original empty update hook, called by Actor::job1_2.
    void sub_7100D77EAC(Actor* actor);
    // 0x7100d78028: the awareness entry at +0x18.
    Unk_71024dc978* m8() override;

    // inline-only in the original; name is a guess. The same inlined update (`if (_48 < level)
    // _48 = level; _44 |= is_target_npc`) appears in EmitInterest::m7, SpeedEmitInterest::m7 and
    // PlayerEmitInterest::m7 (the latter calls it from both arms of the naked / clothed choice).
    void emitInterest(s32 level, bool is_target_npc) {
        if (_18._48 < level)
            _18._48 = level;
        _18._44 |= is_target_npc;
    }

    // TODO: a second polymorphic base (only a virtual destructor; secondary vtable at
    // 0x71024dc958) sits here; not modelled yet.
    /* 0x10 */ u8 _10[0x18 - 0x10];
    /* 0x18 */ Unk_71024dc858 _18;  // _18._44: flags, _18._48: level (EmitInterest behaviors)
    /* 0x70 */ Actor* _70;
    /* 0x78 */ u16 _78;
};
KSYS_CHECK_SIZE_NX150(Unk_71024dc900, 0x80);

// Placeholder name (vtable 0x71024dccf8; D1 0x7100d7f0dc, D0 0x7100d7f104): base of the filters used
// to iterate over the awareness entries (sub_7100D7EEE8). ~48 derived classes (vtables
// 0x7102451358-0x7102451830 for the shared ones in the AI utility TU 0x7100744bb8-0x7100747a00, more
// in single AI TUs) are built on the stack by AI code: the inline ctor leaves _8 = -1 and the rest 0.
// A filter can be linked into its owner's list (AwarenessInstance::_2e8); the dtor unlinks it.
class Unk_71024dccf8 {
public:
    Unk_71024dccf8() = default;
    virtual ~Unk_71024dccf8();
    // Returns true if `entry` should be visited.
    virtual bool m2(Unk_71024dc978* entry) = 0;

    /* 0x08 */ s32 _8 = -1;  // index of the last visited entry
    /* 0x10 */ Unk_71024dccf8* _10 = nullptr;  // previous in the owner's list
    /* 0x18 */ Unk_71024dccf8* _18 = nullptr;  // next in the owner's list
    /* 0x20 */ AwarenessInstance* _20 = nullptr;  // owner
};
KSYS_CHECK_SIZE_NX150(Unk_71024dccf8, 0x28);

// 0x7100d78e30 (in the TU of Unk_71024dc858, not inlined by its callers): `array->at(idx)`.
Unk_7100d78e50* sub_7100D78E30(const sead::ObjArray<Unk_7100d78e50>* array, s32 idx);

// 0x7100d7eee8: returns the next entry of `array` (after filter->_8) that the filter accepts and
// stores its index in filter->_8; nullptr at the end.
Unk_7100d78e50* sub_7100D7EEE8(sead::ObjArray<Unk_7100d78e50>* array, Unk_71024dccf8* filter);

// FIXME. The per-actor awareness object (Actor::mAwareness, Actor+0x550). CSV names some of its
// methods "ActorAwareness::*".
class AwarenessInstance {
public:
    AwarenessInstance();
    virtual ~AwarenessInstance();

    // 0x7100d7c59c: `_300 = 0; _304 = -1`, clears the entries of this instance and of the enabled sensors.
    void calcForEvent();
    void calc();
    void calc2();

    void sleep();
    void disable();
    bool enable();
    // 0x7100d7c494: _2f8 = max(the largest `sensor->m14() * sensor->_4c` (at least 0), _2f4).
    void sub_7100D7C494();
    void sub_7100D7EBE0(f32 value);
    void sub_7100D7EC14(int idx, f32 value);
    f32 sub_7100D7EC34(int idx) const;

    // Removes `filter` from the list of registered filters (_2e8). Called by the filter dtor.
    void sub_7100D7EA7C(Unk_71024dccf8* filter);
    // 0x7100d7e9bc: activates sensor `idx` (registering the instance with Awareness if no sensor
    // was active); 0x7100d7eae4: clears and deactivates it (deregistering if none is left active).
    bool sub_7100D7E9BC(int idx);
    // inline-only in the original; name is a guess (the same sequence is inlined twice into
    // InterestNeckControl::m7): the awareness entry at position `i` of the sorted list, or null.
    Unk_7100d78e50* getSortedEntry(s32 i) {
        if (_308 > i) {
            const SortedEntry entry = _280[i];
            auto* sensor = _260[entry.sensor];
            if (sensor->_8.size() > entry.entry)
                return sub_7100D78E30(&sensor->_8, entry.entry);
        }
        return nullptr;
    }
    // 0x7100d7e74c (lane4 s23): sets the interest level of the sensor `_260[0]` (a request with `_c` = level, m4 then m6).
    bool sub_7100D7E74C(f32 level);
    // 0x7100d7e7e8 (placeholder name): whether m11() holds for all four sensors; disables the instance if it is
    // registered.
    bool sub_7100D7E7E8();
    // 0x7100d7e6f4: passes `request` to the m6 of the sensor `_260[idx]`; on success recomputes the interest level.
    bool sub_7100D7E6F4(Unk_71023e2708* request, int idx);
    void sub_7100D7EAE4(int idx);
    // 0x7100d7e964: whether a sensor is active (else whether the instance is registered).
    bool sub_7100D7E964() const;

    // Placeholder: element of `_280` (sensor index, index in that sensor's `_8`).
    struct SortedEntry {
        s32 sensor;
        s32 entry;
    };

    /* 0x008 */ sead::ObjArray<Unk_7100d78e50> _8;  // awareness entries (allocBuffer 0x7100d78d44)
    /* 0x028 */ u8 _28[0x230 - 0x28];
    /* 0x230 */ sead::Matrix34f _230;  // base matrix of the awareness (the forward axis is read by BokoblinRestraint)
    sead::SafeArray<Unk_71024dce08*, 4> _260;
    /* 0x280 */ sead::Buffer<SortedEntry> _280;  // the entries ordered by distance (placeholder name)
    /* 0x290 */ u8 _290[0x2c8 - 0x290];
    /* 0x2c8 */ sead::Vector3f _2c8;  // base position of the awareness
    /* 0x2d4 */ sead::Vector3f _2d4;
    /* 0x2e0 */ Actor* _2e0;  // the owner
    /* 0x2e8 */ Unk_71024dccf8* _2e8;  // first registered filter
    /* 0x2f0 */ u8 _2f0[4];
    /* 0x2f4 */ f32 _2f4;  // lower limit of _2f8
    /* 0x2f8 */ f32 _2f8;  // the largest interest level of the active sensors (sub_7100D7C494)
    /* 0x2fc */ u8 _2fc[4];
    /* 0x300 */ s32 _300;  // checked before EnemyNormal::m47 (no search when 0)
    /* 0x304 */ s32 _304;  // set to -1 by calcForEvent
    /* 0x308 */ s32 _308;  // number of valid `_280` entries
    /* 0x30c */ u8 _30c[0x318 - 0x30c];
    /* 0x318 */ u32 _318;  // bit 3 follows !IsInHyruleCastleArea (EnemyRoot::sub_71003B5644)
    /* 0x31c */ u8 _31c[0x328 - 0x31c];
    /* 0x328 */ u32 _328;  // WolfLinkRoot::enter_ (0x2000b8)
    /* 0x32c */ u8 _32c[0x334 - 0x32c];
    s8 _334;
    u8 _335[0x337 - 0x335];
    /* 0x337 */ bool _337;  // registered with Awareness::Instances
    u32 _338;
};
KSYS_CHECK_SIZE_NX150(AwarenessInstance, 0x340);

}  // namespace ksys::act
