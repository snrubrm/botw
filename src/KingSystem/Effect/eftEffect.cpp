#include "KingSystem/Effect/eftEffect.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementAreaMgr.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include <xlink2/xlink2UserInstanceELink.h>
#include <xlink2/xlink2ResourceAccessor.h>
#include <xlink2/xlink2ResourceAccessorELink.h>

namespace ksys::eft {

SEAD_SINGLETON_DISPOSER_IMPL(Effect)

void Unk_EffectActorTable::sub_7100DA2118() {
    // NON_MATCHING: SDK range iteration uses a different counter instead of the native paired loop.
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mCount = 0;
    for (auto& entry : _0) {
        entry.actor = nullptr;
        entry._28 = false;
    }
}

// NON_MATCHING: iterator unrolling, handle-copy scheduling, and saturating count differ.
bool Unk_EffectActorTable::sub_7100DA216C(act::Actor* actor, const sead::Vector3f& position) {
    static const char* const names[] = {"FallLeaves_A", "FallLeaves_B", "FallLeaves_C", "FallLeaves_D",
                                  "FallLeaves_E"};
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    auto* xlink = actor->getXLink();
    if (!xlink || !xlink->_48)
        return false;
    if (map::PlacementMgr::instance()->mPlacementActors->mStruct1->mFlags.isOn(
            map::PlacementAreaMgr::Flag::LastBoss))
        return false;
    const s32 value = xlink->_48->getResourceAccessor().getUserCustomParamValueInt(0);
    for (auto& entry : _0) {
        if (entry.actor)
            continue;
        entry.actor = actor;
        entry.position = position;
        if (value && act::Reaction::instance()->_28) {
            const char* name = "";
            if (value >= 1 && value <= 5)
                name = names[value - 1];
            entry.handle = searchAndEmitELink(act::Reaction::instance()->_28, name);
            entry.handle.setPosition(position);
            entry._28 = true;
        }
        mCount = sead::Mathi::min(mCount + 1, 32);
        return true;
    }
    return false;
}

bool Unk_EffectActorTable::sub_7100DA2330(act::Actor* actor) {
    // NON_MATCHING: iterator addressing/unrolling and the saturating decrement differ.
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (auto& entry : _0) {
        if (entry.actor == actor) {
            entry.actor = nullptr;
            mCount = sead::Mathi::max(mCount - 1, 0);
            return true;
        }
    }
    return false;
}

}  // namespace ksys::eft
