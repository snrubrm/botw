#include "Game/Actor/actLastBoss.h"
#include <basis/seadNew.h>
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::act {

Unk_71025ae680* LastBoss::m178(sead::Heap* heap) {
    return new (heap) Unk_710244eb48(this);
}

namespace {
void forwardX17ToParts(ksys::act::Actor* actor, ksys::act::Unk117* arg) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return;
    auto* enemy = static_cast<Enemy*>(actor);
    for (auto* part : enemy->_1128.mList) {
        if (auto* part_actor =
                sead::DynamicCast<ksys::act::Actor>(part->mLink.getProc(nullptr, nullptr)))
            part_actor->x_17(arg);
    }
}
}  // namespace

void LastBoss::initMaybe() {
    if (auto* x = _1250) {
        if (auto* y = x->_18)
            y->m0();
    }
    if (auto* body = findPhysicsBodyByName(sub_71007A250C()->cstr(), "BgSensor")) {
        if (!body->isAddedToWorld()) {
            body->addToWorld();
            body->setContactAll();
            body->setFlag1000000();
        }
    }
    Enemy::initMaybe();
}

// 0x71002c5978: m159() is the controller; DynamicCast<Unk_710244eb48> has its own function-local static.
void LastBoss::stunEnd() {
    if (auto* controller = sead::DynamicCast<Unk_710244eb48>(m159()))
        controller->sub_71006E252C();
}

void LastBoss::sub_71002C5B3C() {
    if (auto* controller = sead::DynamicCast<Unk_710244eb48>(m159()))
        controller->_1c = true;
}

void LastBoss::sub_71002C6A78() {
    if (auto* controller = sead::DynamicCast<Unk_710244eb48>(m159()))
        controller->_1c = false;
}

void LastBoss::sub_71002C5A14() {
    if (_1548.mEventFlow)
        _1548.unloadEvent();
    if (_1718.mEventFlow)
        _1718.unloadEvent();
    if (_18e8.mEventFlow)
        _18e8.unloadEvent();
}

void LastBoss::sub_71002C5DB4() {
    if (_1ab8.mEventFlow)
        _1ab8.unloadEvent();
    if (_1c88.mEventFlow)
        _1c88.unloadEvent();
}

void LastBoss::sub_71002C6930() {
    for (auto* part : _1128.mList) {
        if (!part->mLink.hasProcInCalcState())
            continue;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&part->mLink, &accessor);
        if (!accessor.isDeletedOrDeleting())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

void LastBoss::sub_71002C69CC() {
    if (_14f8.mDamageManager)
        return;
    if (auto* damage_mgr = getDamageMgr())
        damage_mgr->addDamageCallback(4, &_14f8);
}

void LastBoss::sub_71002C6A24() {
    if (!_14f8.mDamageManager)
        return;
    if (auto* damage_mgr = getDamageMgr())
        damage_mgr->removeDamageCallback(&_14f8);
}

void LastBoss::m117(ksys::act::Unk117* arg) {
    forwardX17ToParts(this, arg);
}

// NON_MATCHING: member types incomplete
LastBoss::LastBoss(const CreateArg& arg) : Enemy(arg) {}

LastBoss::~LastBoss() = default;

// NON_MATCHING: store schedule only (the original zeroes _14e8 / _14ec with an 8-byte store plus a separate
// word store, and keeps _14d0 / _14e4 / _14f0 separate)
ksys::act::BaseProc* LastBoss::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) LastBoss(arg);
}

void LastBoss::m63() {
    Enemy::m63();
    _14e4 = 0;
    _14e8.makeAllZero();
    const s32 max_life = getMaxLife();
    s32* life = getLife();
    *life = max_life - getNumberOfClearedRemains() * 1000;
    _14f8._34 = 0;
    _1530 = 0;
    _1544 = 0;
    _14f8._30.makeAllZero();
    _14f0 = 1000.0f;
}

void LastBoss::x() {
    if (_14e8.isOnBit(17))
        return;
    if (auto* life = getLife()) {
        if (*life == 0)
            return;
    }
    _14e8.setBit(17);
    if (auto* as_list = mASList) {
        if (as_list->x_1(1, 0) != "Barrier_On")
            as_list->startAnimationMaybe(-1.0f, -1.0f, "Barrier_On", 1, 0, true);
    }
}

void LastBoss::update() {
    if (_14e8.isOnBit(17)) {
        _14e8.resetBit(17);
        auto* as_list = mASList;
        if (!as_list)
            return;
        auto* life = getLife();
        if (life && *life == 0)
            as_list->startAnimationMaybe(-1.0f, -1.0f, "Barrier_Off_Damage_Last", 1, 0, true);
        else if (isSlowTimeMaybe())
            as_list->startAnimationMaybe(-1.0f, -1.0f, "Barrier_Off_AtSlow", 1, 0, true);
        else
            as_list->startAnimationMaybe(-1.0f, -1.0f, "Barrier_Off", 1, 0, true);
    } else {
        auto* as_list = mASList;
        if (!as_list)
            return;
        if (as_list->x_1(1, 0) == "Barrier_Off" || as_list->x_1(1, 0) == "Barrier_Off_AtSlow") {
            if (isSlowTimeMaybe())
                as_list->startAnimationMaybe(-1.0f, -1.0f, "Barrier_Off_AtSlow", 1, 0, true);
            else
                as_list->startAnimationMaybe(-1.0f, -1.0f, "Barrier_Off", 1, 0, true);
        }
    }
}

void LastBoss::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    setter->set(0x20, 0x10);
    _14e8.reset(0x80);
    Enemy::m76(setter);
}

void LastBoss::m77(ksys::VFR::ScopedDeltaSetter* setter) {
    setter->set(0x20, 0x10);
}

bool LastBoss::isGuard() {
    return false;
}

bool LastBoss::isGuardJust() {
    return _14f8._30.isOn(1);
}

bool LastBoss::sub_71002C6210(f32 value) const {
    return _14f0 < value;
}

bool LastBoss::m140() {
    return _14e8.isOnBit(9);
}

}  // namespace uking::act

// inline-only in the original; name is a guess (same helper as in acc::Weapon / acc::Armor).
static ksys::act::BaseProc* getProcIfActor(ksys::act::BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<ksys::act::Actor>(proc))
        return proc;
    return nullptr;
}

uking::act::LastBoss* sub_71002C6B30(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = static_cast<ksys::act::Actor*>(getProcIfActor(accessor.getProc()));
    return sead::DynamicCast<uking::act::LastBoss>(actor);
}

bool sub_71002C6B0C(const ksys::act::ActorConstDataAccess& accessor) {
    auto* boss = sub_71002C6B30(accessor);
    return boss ? boss->_14e4 == 1 : false;
}

void sub_71002C64A0(sead::Vector3f* out, ksys::act::Actor* actor) {
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    sead::Vector3f home;
    actor->getHomePos(&home);
    const sead::Vector3f diff = pos - home;
    sead::Vector3f side;
    side.setCross(diff, sead::Vector3f::ey);
    sead::Vector3f dir;
    dir.setCross(side, diff);
    dir.normalize();
    *out = pos + dir * 2.0f;
}

void sub_71002C682C(ksys::act::Actor* actor, f32 value) {
    auto* enemy = sead::DynamicCast<uking::act::Enemy>(actor);
    if (!enemy)
        return;
    for (auto* part : enemy->_1128.mList) {
        if (!part->mLink.hasProcInCalcState())
            continue;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&part->mLink, &accessor);
        accessor.sub_7100D153A4(value);
    }
}
