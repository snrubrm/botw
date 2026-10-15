#include "Game/Actor/Action/actionRodMagicPhysBall.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySphere.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

RodMagicPhysBall::RodMagicPhysBall(const InitArg& arg) : ChemicalPhysBall(arg) {}

RodMagicPhysBall::~RodMagicPhysBall() = default;

void RodMagicPhysBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalPhysBall::enter_(params);
    _d8.reset();
    _160 = false;
    _161 = false;
    _1a8._c = true;
    sub_710023B234(&_1a8);
}

void RodMagicPhysBall::leave_() {
    if (_160)
        mActor->sub_71011DA834(&_e8);
    ChemicalPhysBall::leave_();
}

void RodMagicPhysBall::loadParams_() {
    ChemicalPhysBall::loadParams_();
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getStaticParam(&mChemicalType_s, "ChemicalType");
    getStaticParam(&mBgCheckHeight_s, "BgCheckHeight");
}

// NON_MATCHING: the original loads the argument of `_e8.sub_7100D3C5E0(mActor)` as `ldr x1, [x19, #0x8]`; ours reuses
// the `&mActor` register (`ldr x1, [x20]`) of the neighbouring mActor loads. Nothing else differs.
void RodMagicPhysBall::calc_() {
    bool flag = false;
    if (sub_710023B458(&flag)) {
        if (flag && *mChemicalType_s == 0)
            xlinkSearchAndEmit(mActor, "Explode", 2, &_168[0]);
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    if (mActor->get68f().load() || _d8.hasProc())
        sub_710023B7B4();
    ChemicalPhysBall::calc_();
    if (_160) {
        auto* actor = _e8.sub_7100D3C5E0(mActor);
        if (!actor || actor->getState() != ksys::act::BaseProc::State::Calc)
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    } else if (*mChemicalType_s == 0) {
        const bool hit = isBgGroundHit(mActor, false) || isLandedMaybe(mActor, false);
        if (hit && !_161)
            xlinkSearchAndEmit(mActor, "Rebound", 2, &_168[1]);
        _161 = hit;
    }
}

bool RodMagicPhysBall::m33() {
    return false;
}

f32 RodMagicPhysBall::m40() {
    f32 time = *mDeleteTime_s;
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor)) {
        if (bullet->_cf8 >= 0.0f)
            time = bullet->_cf8;
    }
    return time;
}

bool RodMagicPhysBall::sub_710023B234(Unk1a8* out) {
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor)) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&bullet->_ba0, &accessor);
        if (accessor.hasProc()) {
            accessor.getActorMtx().getTranslation(out->_0);
            return true;
        }
    }
    return false;
}

// NON_MATCHING: accessor initialization stores are reordered.
bool RodMagicPhysBall::sub_710023B458(bool* out) {
    auto* actor = mActor;
    if (!actor)
        return false;

    switch (*mChemicalType_s) {
    case 0:
        if (hasAttackInfo(actor)) {
            if (auto* info = getAttackInfo(actor, 0)) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&info->_50, &accessor);
                if (ksys::act::isPlayerProfile(accessor) || ksys::act::isEnemyProfile(accessor) ||
                    ksys::act::isBulletProfile(accessor) || ksys::act::isHorseProfile(accessor) ||
                    ksys::act::isNPCProfile(accessor) || sead::DynamicCast<act::Enemy>(accessor.getProc())) {
                    *out = true;
                    return true;
                }
                if (accessor.sub_7100D13290(0)) {
                    _d8 = info->_50;
                    return false;
                }
            }
        }
        break;
    case 1:
        if (sub_710023BE44())
            return true;
        if (_a4 > m34())
            return true;
        return _b4 && _a8.value <= sead::Mathf::epsilon();
    case 2:
        if (hasAttackInfo(actor)) {
            if (auto* info = getAttackInfo(actor, 0)) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&info->_50, &accessor);
                if (ksys::act::isEnemyProfile(accessor)) {
                    if (accessor.sub_7100D135A0(-1) > 0.1f)
                        _d8 = info->_50;
                    *out = true;
                    return true;
                }
                if (ksys::act::isPlayerProfile(accessor) || ksys::act::isBulletProfile(accessor) ||
                    ksys::act::isHorseProfile(accessor) || ksys::act::isNPCProfile(accessor) ||
                    sead::DynamicCast<act::Enemy>(accessor.getProc())) {
                    *out = true;
                    return true;
                }
                if (accessor.sub_7100D1336C(0)) {
                    _d8 = info->_50;
                    *out = true;
                    return true;
                }
            }
        }
        break;
    }

    if (mActor->get68f().load())
        return true;
    if (_a4 > m34())
        return true;
    return _b4 && _a8.value <= sead::Mathf::epsilon();
}

// NON_MATCHING: vector copies, saved registers and ray endpoint stores are reordered.
bool RodMagicPhysBall::sub_710023BE44() {
    if (!mActor)
        return false;
    auto* body = sead::DynamicCast<ksys::phys::SphereRigidBody>(mActor->getMainBody());
    if (!body)
        return false;
    const f32 radius = body->getRadius();
    sead::Vector3f velocity;
    body->getLinearVelocity(&velocity);
    sead::Vector3f direction = velocity;
    direction.normalize();
    velocity *= 1.0f / 30.0f;
    velocity *= ksys::VFR::instance()->getDeltaFrame();
    sead::Vector3f position;
    body->getPosition(&position);
    const sead::Vector3f end = direction * radius + position + velocity;
    sead::Vector3f start = position;
    if (_1a8._c)
        start -= direction * 3.0f;
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.setStartAndEnd(start, end);
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        if (_1a8._c) {
            sead::Vector3f hit_position;
            query.getHitPosition(&hit_position);
            hit_position -= sead::Vector3f(_1a8._0.x, position.y, _1a8._0.z);
            hit_position.normalize();
            if (direction.dot(hit_position) >= 0.0f)
                return true;
        } else {
            if (*mBgCheckHeight_s < 0.0f)
                return true;
            _1a8._d[0] = true;
        }
    }
    _1a8._c = false;
    if (*mBgCheckHeight_s < 0.0f)
        return false;
    query.resetCastResult();
    {
        sead::Vector3f elevated_start = start;
        sead::Vector3f elevated_end = end;
        elevated_start.y += *mBgCheckHeight_s;
        elevated_end.y += *mBgCheckHeight_s;
        query.setStartAndEnd(elevated_start, elevated_end);
        if (query.worldRayCast(ksys::phys::ContactLayerType::Entity))
            _1a8._d[1] = true;
    }
    query.resetCastResult();
    {
        sead::Vector3f elevated_start = start;
        sead::Vector3f elevated_end = end;
        elevated_start.y += *mBgCheckHeight_s * 2.0f;
        elevated_end.y += *mBgCheckHeight_s * 2.0f;
        query.setStartAndEnd(elevated_start, elevated_end);
        if (query.worldRayCast(ksys::phys::ContactLayerType::Entity))
            _1a8._d[2] = true;
    }
    return _1a8._d[0] && _1a8._d[1] && _1a8._d[2];
}

int RodMagicPhysBall::m36() {
    const int type = *mChemicalType_s;
    int flags = ChemicalAttack::m36();
    if (type == 1)
        flags |= 8;
    return flags;
}

}  // namespace uking::action
