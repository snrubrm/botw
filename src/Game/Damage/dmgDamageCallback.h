#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Damage/dmgDamageManagerBase.h"

namespace uking::dmg {

class DamageManagerBase;

// The object the damage manager builds on the stack and passes to the damage callbacks as their last
// argument (vtable 0x710244e090, RTTI static 0x71025af120; DamageMgr::m22 / m22_x_0 / m55 construct it
// with `mFlags` = the manager's field 0x8c and store `mFlags` back after the callbacks ran). Placeholder
// name (its RTTI parent, typeinfo static 0x71025af130, has no other user).
class DamageCallbackInfoBase {
    SEAD_RTTI_BASE(DamageCallbackInfoBase)
};

class DamageCallbackInfo : public DamageCallbackInfoBase {
    SEAD_RTTI_OVERRIDE(DamageCallbackInfo, DamageCallbackInfoBase)
public:
    u32 mFlags;
};

// FIXME: incomplete
class DamageCallback {
    SEAD_RTTI_BASE(DamageCallback)
public:
    virtual ~DamageCallback() {
        if (mDamageManager)
            mDamageManager->removeDamageCallback(this);
    }
    virtual void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, DamageCallbackInfo* a6) = 0;

    DamageCallback* mPrev{};
    DamageCallback* mNext{};
    DamageManagerBase* mDamageManager{};  // Might be a different base class(Interface?)
    u32 mEventId{};
};

}  // namespace uking::dmg

namespace ksys::act {
class Actor;
}

// 0x71005da048 (CSV name; namespace unknown): registers `callback` with the actor's damage manager.
bool setDamageCallbackTiming(ksys::act::Actor* actor, s32 timing, uking::dmg::DamageCallback* callback);
// 0x71005da114: unregisters `callback` from the actor's damage manager.
bool sub_71005DA114(ksys::act::Actor* actor, uking::dmg::DamageCallback* callback);
