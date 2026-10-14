#include "KingSystem/ActorSystem/actActorBind.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"

// Source owner unknown; these global helpers are adjacent to ActorBind in the original.
bool sub_71006E8610(ksys::act::Actor* actor) {
    if (!actor)
        return false;
    auto* param = actor->getParam();
    if (!param)
        return false;
    auto* damage = param->getRes().mDamageParam;
    return damage && damage->mIsMetamorBurnout.ref();
}

bool sub_71006E8644(ksys::act::Actor* actor) {
    if (!actor)
        return false;
    auto* param = actor->getParam();
    if (!param)
        return false;
    auto* damage = param->getRes().mDamageParam;
    if (!damage)
        return false;
    return damage->mIsDeadBurnout.ref() || damage->mIsDeadIce.ref() ||
           damage->mIsDeadElectric.ref() || damage->mIsMetamorBurnout.ref() ||
           damage->mIsMetamorIce.ref() || damage->mIsMetamorElectric.ref() ||
           damage->mColdWaterFrozenTime.ref() >= 0 || damage->mHeavySnowColdTime.ref() >= 0 ||
           damage->mHotWaterBoiledTime.ref() >= 0;
}

namespace ksys::act {

ActorBind::ActorBind() = default;

Actor* ActorBind::sub_7100D3C5E0(BaseProc* proc) {
    BaseProc* other = _20 ? _20 : proc;
    auto* actor = sead::DynamicCast<Actor>(_8.getProc(nullptr, other));
    if (actor && actor->_738.hasProc()) {
        ActorLinkConstDataAccess accessor;
        acquireActor(&actor->_738, &accessor);
        if (accessor.isStateCalc()) {
            _8 = actor->_738;
            actor = sead::DynamicCast<Actor>(_8.getProc(nullptr, other));
        }
    }

    if (actor && actor->isCalc() && actor->mSpecialJobTypesMaskOverride.isOnBit(1))
        return actor;
    return nullptr;
}

gsys::Model* ActorBind::sub_7100D3C770(BaseProc* proc) {
    auto* actor = sub_7100D3C5E0(proc);
    return actor ? actor->getModel() : nullptr;
}

// NON_MATCHING: the original merges the two false paths into `and w0, w9, w8`
bool ActorBind::m6(BaseProc* proc) {
    auto* actor = sub_7100D3C5E0(proc);
    return actor && actor->getPhysics() &&
           actor->getPhysics()->getFlags().isOn(phys::InstanceSet::Flag::_8);
}

// NON_MATCHING: the original merges the two false paths into `and w0, w9, w8`
bool ActorBind::m7(BaseProc* proc) {
    auto* actor = sub_7100D3C5E0(proc);
    return actor && actor->getPhysics() &&
           actor->getPhysics()->getFlags().isOn(phys::InstanceSet::Flag::_10);
}

// NON_MATCHING: the original merges the two false paths into `and w0, w9, w8`
bool ActorBind::m8(BaseProc* proc) {
    auto* actor = sub_7100D3C5E0(proc);
    return actor && actor->getPhysics() &&
           actor->getPhysics()->getFlags().isOn(phys::InstanceSet::Flag::DisableDraw);
}

void ActorBind::m9(BaseProc* proc) {
    auto* actor = sub_7100D3C5E0(proc);
    if (!actor)
        return;
    auto* physics = actor->getPhysics();
    if (!physics)
        return;
    auto* own_physics = static_cast<Actor*>(proc)->getPhysics();
    if (!own_physics)
        return;
    own_physics->sub_7100FB9BAC(physics);
}

}  // namespace ksys::act
