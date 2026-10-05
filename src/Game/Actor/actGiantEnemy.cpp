#include "Game/Actor/actGiantEnemy.h"
#include "Game/Actor/actGiantArmor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::act {

// NON_MATCHING: member types incomplete
GiantEnemy::~GiantEnemy() = default;

void GiantEnemy::m56(sead::Vector3f* pos) {
    if (_1560 && _1560->isAddedToWorld())
        _1560->getCenterOfMassInWorld(pos);
    else
        x_18(pos);
}

void GiantEnemy::killWithDropsAndEffects(int a1) {
    Enemy::killWithDropsAndEffects(a1);
    incrementGiantOrSandwormDefeatCount();
}

void GiantEnemy::calcMaybe() {
    Enemy::calcMaybe();
}

void GiantEnemy::setNecklaceFlag(s32 index) {
    if (index >= 2 && ksys::act::hasTag(this, ksys::act::tags::UseNecklaceSaveFlag))
        Enemy::setNecklaceFlag(index);
}

void GiantEnemy::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    _14c8.sub_710002A94C(this);
    Enemy::m76(setter);
}

void GiantEnemy::m117(ksys::act::Unk117* arg) {
    Enemy::m117(arg);
    _14c8.sub_710002A828(arg);
}

void GiantEnemy::m63() {
    if (_1558)
        _1558->m2();
    Enemy::m63();
}

bool GiantEnemy::m146() {
    const bool result = Enemy::m146();
    if (!_1568 && _1558)
        _1558->m3();
    return result;
}

void GiantEnemy::initMaybe() {
    Enemy::initMaybe();
    if (!_1510.mDamageManager)
        getDamageMgr()->addDamageCallback(0, &_1510);
}

bool GiantEnemy::startPreparingForPreDelete_() {
    if (!Enemy::startPreparingForPreDelete_())
        return false;
    if (auto* damage = getDamageMgr())
        damage->removeDamageCallback(&_1510);
    return true;
}

void GiantEnemy::preDelete2_(const PreDeleteArg& arg) {
    if (_1558) {
        _1558->m5();
        _1558 = nullptr;
    }
    Enemy::preDelete2_(arg);
}

void GiantEnemy::onSleepRequested_(SleepWakeReason reason) {
    DynamicActor::onSleepRequested_(reason);
    _14c8.sub_710002A544(reason);
}

void GiantEnemy::onWakeUpRequested_(SleepWakeReason reason) {
    Actor::onWakeUpRequested_(reason);
    _14c8.sub_710002A63C(reason);
}

void GiantEnemy::onDeleteRequested_(DeleteReason reason) {
    Enemy::onDeleteRequested_(reason);
    _14c8.sub_710002A734();
}

void* GiantEnemy::m119() {
    if (_1558)
        return _1558->m8();
    return nullptr;
}

void GiantEnemy::m145() {}

void GiantEnemy::m110(f32* a1, s32* a2) {
    // tag hash 0xa4c7ba34 (no name known)
    if (ksys::act::hasTag(this, 0xA4C7BA34u)) {
        *a1 = 0.4f;
        *a2 = 0;
    } else {
        Actor::m110(a1, a2);
    }
}

void GiantEnemy::m111(f32* a1, s32* a2) {
    // tag hash 0xa4c7ba34 (no name known)
    if (ksys::act::hasTag(this, 0xA4C7BA34u)) {
        *a1 = 0.4f;
        *a2 = 2;
    } else {
        Actor::m111(a1, a2);
    }
}

void GiantEnemy::m112(f32* a1, s32* a2) {
    // tag hash 0xa4c7ba34 (no name known)
    if (ksys::act::hasTag(this, 0xA4C7BA34u)) {
        *a1 = 0.4f;
        *a2 = 0;
    } else {
        Actor::m112(a1, a2);
    }
}

void GiantEnemy::m113(f32* a1, s32* a2) {
    // tag hash 0xa4c7ba34 (no name known)
    if (ksys::act::hasTag(this, 0xA4C7BA34u)) {
        *a1 = 0.4f;
        *a2 = 2;
    } else {
        Actor::m113(a1, a2);
    }
}

void GiantEnemy::Unk1::sub_710002A544(ksys::act::BaseProc::SleepWakeReason reason) {
    for (auto& link : _8) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.hasProc())
            accessor.sleep(reason);
    }
}

void GiantEnemy::Unk1::sub_710002A63C(ksys::act::BaseProc::SleepWakeReason reason) {
    for (auto& link : _8) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.hasProc())
            accessor.wakeUp(reason);
    }
}

void GiantEnemy::Unk1::sub_710002A734() {
    for (auto& link : _8) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.hasProc())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

void GiantEnemy::Unk1::sub_710002A828(ksys::act::Unk117* arg) {
    for (auto& link : _8) {
        if (auto* armor = sead::DynamicCast<GiantArmor>(
                sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, nullptr))))
            armor->x_17(arg);
    }
}

}  // namespace uking::act
