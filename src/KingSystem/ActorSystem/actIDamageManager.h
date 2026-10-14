#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <mc/seadJobQueue.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace uking::act {
class DamageCallback;
class Struct20Base;
}  // namespace uking::act

namespace ksys::act {

class Actor;

// The RTTI root of the damage managers (unofficial name, upstream 419f8f46b): it holds the damage callback list,
// and its code links among the ActorSystem objects. The original vtables start with checkDerivedRuntimeTypeInfo /
// getRuntimeTypeInfo (slots 0-1), followed by the destructors (slots 2-3). RTTI static 0x71025ae5c0.
class IDamageManager {
    SEAD_RTTI_BASE(IDamageManager)
public:
    explicit IDamageManager(Actor* actor) : mActor(actor) {}
    virtual ~IDamageManager() = default;

    virtual u32 getDamage() = 0;
    virtual s32 getField48() = 0;
    virtual s32 getMinDmg() = 0;
    virtual s32 getField50() = 0;
    virtual s32 getField54() = 0;
    virtual bool checkDamageFlags(s32 bit) = 0;
    virtual u64 getFlags2() = 0;
    virtual void addDamageCallback(s32 eventId, uking::act::DamageCallback* callback);
    virtual void removeDamageCallback(uking::act::DamageCallback* callback);

    // Sturct20 for Damage receive/send?
    uking::act::Struct20Base* mStruct20_a = nullptr;
    uking::act::Struct20Base* mStruct20_b = nullptr;

    Actor* mActor = nullptr;

    sead::Buffer<uking::act::DamageCallback*> mCallbacks{};

    // Lock word guarding mStruct20_a (ForkStalEnemyForceDamage::calc_ does
    // mField_30.lock() / .unlock() around mStruct20_a->combineMaybe(); the inline
    // JobQueueLock sequences match the original exactly).
    sead::JobQueueLock mField_30;
    s8 mField_34 = 0;
};

}  // namespace ksys::act
