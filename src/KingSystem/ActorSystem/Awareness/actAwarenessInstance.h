#pragma once

#include <basis/seadTypes.h>
#include <container/seadObjArray.h>
#include <container/seadSafeArray.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Unk_71024dc858;

// Placeholder name (vtable 0x71024dce08): base class of the four sensor objects an
// AwarenessInstance owns (created in 0x7100d7b974; derived vtables e.g. 0x71024dcea8).
// TODO: incomplete.
class Unk_71024dce08 {
public:
    virtual ~Unk_71024dce08();

    /* 0x08 */ sead::ObjArray<Unk_71024dc858> _8;
    /* 0x28 */ u8 _28[0x3c - 0x28];
    /* 0x3c */ u32 _3c;
    /* 0x40 */ u8 _40[0x4c - 0x40];
    /* 0x4c */ f32 _4c;
    /* 0x50 */ bool _50;  // active (AwarenessInstance::sub_7100D7E9BC / sub_7100D7EAE4)
};

// Placeholder name (vtable 0x71024dc978, RTTI static 0x71025af288): abstract base of the entries of
// the awareness arrays (AwarenessInstance::_8, sensor::_8); the filters get them through this type.
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
};

// Placeholder name (vtable 0x71024dc858, RTTI static 0x71025af278, ctor 0x7100d771cc, D1
// 0x7100d772d4, size 0xb0): one entry of AwarenessInstance::_8 (an awareness target).
// TODO: incomplete (virtual functions not declared).
class Unk_71024dc858 : public Unk_71024dc978 {
    SEAD_RTTI_OVERRIDE(Unk_71024dc858, Unk_71024dc978)
public:
    Unk_71024dc858();
    ~Unk_71024dc858() override;

    f32 m4(int idx) override;
    bool m5(int bit) const override;
    sead::BitFlag16* m6() override;
    bool m7(sead::Vector3f* pos) override;
    bool m8(sead::Vector3f* vel) override;
    void m9(int idx, f32 value) override;
    void m10(int bit, bool on) override;

    /* 0x08 */ BaseProcLink mLink;  // the target actor
    /* 0x18 */ sead::SafeArray<f32, 4> _18{{1.0, 0, 0, 1.0}};  // m4 / m9
    /* 0x28 */ sead::SafeArray<f32, 4> _28{{1.0, 1.0, 1.0, 1.0}};  // m4
    /* 0x38 */ sead::BitFlag16 _38;  // m5 / m6 / m10
    /* 0x3c */ u32 _3c = 0;
    /* 0x40 */ u32 _40 = 0;
    /* 0x44 */ u32 _44 = 0;
    /* 0x48 */ u32 _48 = 0;
    /* 0x4c */ f32 _4c = -1.0;
    /* 0x50 */ u16 _50 = 0;
    /* 0x52 */ u8 _52[0x58 - 0x52];
    /* 0x58 */ sead::Matrix34f _58;  // passed as a matrix by EnemyCalledAppear::calc_ (sub_71005D8DE8)
    /* 0x88 */ u8 _88[0xa0 - 0x88];
    /* 0xa0 */ s32 _a0;  // kind (e.g. 2 checked by BeeSwarmNormal::m47)
    /* 0xa4 */ f32 _a4;  // compared with StoneOctarockGuardNearTarget NoticeTerrorLevel
    /* 0xa8 */ f32 _a8;  // distance-like value compared by many AI functions
    /* 0xac */ u32 _ac;
};
KSYS_CHECK_SIZE_NX150(Unk_71024dc858, 0xb0);

class AwarenessInstance;

// Placeholder name (vtable 0x71024dc900; RTTI; created by 0x71011c57c0 (CSV Actor::x_27) with
// new(0x80)): Actor::_548. Contains an awareness entry at +0x18 (vtable 0x71024dc858, ctor
// 0x7100d77254 (entry, actor)), the actor at +0x70 and a u16 at +0x78; a second base at +0x10.
// TODO: incomplete (only the virtual slot used by player actions is declared).
class Unk_71024dc900 {
    SEAD_RTTI_BASE(Unk_71024dc900)
public:
    virtual ~Unk_71024dc900();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    // 0x7100d78028: the awareness entry at +0x18.
    virtual Unk_71024dc978* m8();
};

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
Unk_71024dc858* sub_7100D78E30(const sead::ObjArray<Unk_71024dc858>* array, s32 idx);

// 0x7100d7eee8: returns the next entry of `array` (after filter->_8) that the filter accepts and
// stores its index in filter->_8; nullptr at the end.
Unk_71024dc858* sub_7100D7EEE8(sead::ObjArray<Unk_71024dc858>* array, Unk_71024dccf8* filter);

// FIXME. The per-actor awareness object (Actor::mAwareness, Actor+0x550). CSV names some of its
// methods "ActorAwareness::*".
class AwarenessInstance {
public:
    AwarenessInstance();
    virtual ~AwarenessInstance();

    void calcForEvent();
    void calc();
    void calc2();

    void sleep();
    void disable();
    bool enable();
    void sub_7100D7C494();
    void sub_7100D7EBE0(f32 value);
    void sub_7100D7EC14(int idx, f32 value);
    f32 sub_7100D7EC34(int idx) const;

    // Removes `filter` from the list of registered filters (_2e8). Called by the filter dtor.
    void sub_7100D7EA7C(Unk_71024dccf8* filter);
    // 0x7100d7e9bc: activates sensor `idx` (registering the instance with Awareness if no sensor
    // was active); 0x7100d7eae4: clears and deactivates it (deregistering if none is left active).
    bool sub_7100D7E9BC(int idx);
    void sub_7100D7EAE4(int idx);
    // 0x7100d7e964: whether a sensor is active (else whether the instance is registered).
    bool sub_7100D7E964() const;

    /* 0x008 */ sead::ObjArray<Unk_71024dc858> _8;  // awareness entries (allocBuffer 0x7100d78d44)
    /* 0x028 */ u8 _28[0x260 - 0x28];
    sead::SafeArray<Unk_71024dce08*, 4> _260;
    /* 0x280 */ u8 _280[0x2e8 - 0x280];
    /* 0x2e8 */ Unk_71024dccf8* _2e8;  // first registered filter
    /* 0x2f0 */ u8 _2f0[0x334 - 0x2f0];
    s8 _334;
    u8 _335[0x337 - 0x335];
    /* 0x337 */ bool _337;  // registered with Awareness::Instances
    u32 _338;
};
KSYS_CHECK_SIZE_NX150(AwarenessInstance, 0x340);

}  // namespace ksys::act
