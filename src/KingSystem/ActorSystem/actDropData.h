#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

namespace uking::dmg {
class DamageManagerBase;
}  // namespace uking::dmg

namespace ksys::act {

class Actor;

// Placeholder name (RTTI static 0x71025ae620; no vtable of its own in the binary). Abstract base
// of DropData and the type returned by Actor::getDropData() (vtable slot 134). Note that the
// destructor comes last in the vtable.
class Unk_71025ae620 {
    SEAD_RTTI_BASE(Unk_71025ae620)
public:
    struct Unk1 {
        s16 _0;
        sead::SafeString _8;
    };

    /*  2 */ virtual void clearFlags() = 0;
    /*  3 */ virtual bool isHappy() = 0;
    /*  4 */ virtual bool isFlag1Set() = 0;
    /*  5 */ virtual bool m5() = 0;
    /*  6 */ virtual bool getDropVelocity(const sead::SafeString& name, sead::Vector3f* velocity,
                                         f32* random) = 0;
    /*  7 */ virtual bool getDropAngVelFromBomb(f32* ang_velocity, f32* random) = 0;
    /*  8 */ virtual bool preloadDropsMaybe(Actor* actor) = 0;
    /*  9 */ virtual void resetPreloadActorsMaybe(Actor* actor) = 0;
    /* 10 */ virtual void initFromActor(Actor* actor) = 0;
    /* 11 */ virtual void getTable(sead::Buffer<Unk1>* table, sead::Buffer<Unk1>* table2,
                                   const sead::Vector3f& pos) = 0;
    /* 12 */ virtual ~Unk_71025ae620() = default;
};

// Name from the CSV (act::DropData::*, 0x71006da914-0x71006dbcb0). Size 0xa90 (Actor::makeDropData),
// vtable 0x710244e178, RTTI static 0x71025ae610.
// TODO: incomplete.
class DropData : public Unk_71025ae620 {
    SEAD_RTTI_OVERRIDE(DropData, Unk_71025ae620)
public:
    void clearFlags() override;
    bool isHappy() override;
    bool isFlag1Set() override;
    bool m5() override;
    bool getDropVelocity(const sead::SafeString& name, sead::Vector3f* velocity,
                         f32* random) override;
    bool getDropAngVelFromBomb(f32* ang_velocity, f32* random) override;
    bool preloadDropsMaybe(Actor* actor) override;
    void resetPreloadActorsMaybe(Actor* actor) override;
    void initFromActor(Actor* actor) override;
    // 0x71006db324 (declaration only; informal CSV name).
    void init(Actor* actor, const sead::SafeString& drop_actor);
    void getTable(sead::Buffer<Unk1>* table, sead::Buffer<Unk1>* table2,
                  const sead::Vector3f& pos) override;
    ~DropData() override;

    /// CSV name "act::DropData::delete": deletes the given object (if any) through its vtable.
    static void sub_71006DB89C(Unk_71025ae620* data);

    /// CSV name "act::DropData::x" (0x71006da914; declaration only, lane4 s28): called by
    /// MapConstActive::m148 with the actor's damage manager (slot 127) and `false`.
    void sub_71006DA914(uking::dmg::DamageManagerBase* damage_mgr, bool a2);

    /* 0x008 */ sead::Atomic<u32> _8 = 0;
    /* 0x00c */ u16 _c = 0;  // flags
    /* 0x00e */ u16 _e = 0;
    /* 0x010 */ Unk1 _10[7][16];
};
KSYS_CHECK_SIZE_NX150(DropData, 0xa90);

}  // namespace ksys::act
