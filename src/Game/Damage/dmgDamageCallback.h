#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Damage/dmgDamageManagerBase.h"

namespace uking::dmg {

class DamageManagerBase;

// FIXME: incomplete
class DamageCallback {
    SEAD_RTTI_BASE(DamageCallback)
public:
    virtual ~DamageCallback() {
        if (mDamageManager)
            mDamageManager->removeDamageCallback(this);
    }
    virtual void call(u32* a1, s32* a2, u32* a3, u32* a4, u32* a5, u64 a6) = 0;

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
