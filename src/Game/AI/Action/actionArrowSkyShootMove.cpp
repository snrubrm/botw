#include "Game/AI/Action/actionArrowSkyShootMove.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::action {

ArrowSkyShootMove::ArrowSkyShootMove(const InitArg& arg) : ArrowShootMove(arg) {}

ArrowSkyShootMove::~ArrowSkyShootMove() = default;

void ArrowSkyShootMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ArrowShootMove::enter_(params);
    _170 = 0;
}

void ArrowSkyShootMove::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    ArrowShootMove::leave_();
}

void ArrowSkyShootMove::loadParams_() {
    ArrowShootMove::loadParams_();
    getStaticParam(&mInterval_s, "Interval");
    getStaticParam(&mSkyShootDist_s, "SkyShootDist");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getDynamicParam(&mPosOffset_d, "PosOffset");
}

void ArrowSkyShootMove::calc_() {
    ArrowShootMove::calc_();
}

// NON_MATCHING: register allocation / stack layout (the original compares _170 with 3, 1, 0 in that
// order and keeps the three hit-position components in different registers).
void ArrowSkyShootMove::m33() {
    if (_170 == 3) {
        ArrowShootMove::m33();
        return;
    }
    if (_170 == 1) {
        if (auto* body = mActor->getMainBody())
            body->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
        _174.update();
        if (_174.value > sead::Mathf::epsilon())
            return;
        sead::Vector3f dir = -sead::Vector3f::ey;
        if (mTargetActor_d) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(mTargetActor_d, &accessor);
            if (accessor.hasProc()) {
                sead::Vector3f pos;
                accessor.getActorMtx().getTranslation(pos);
                pos.x += mPosOffset_d->x;
                pos.y += mPosOffset_d->y;
                pos.z += mPosOffset_d->z;
                sead::Vector3f end(pos.x, pos.y, pos.z);
                end.y = pos.y + *mAtRange_d;
                _180 = end;
                sead::Vector3f hit;
                if (sub_71000A6808(end, &hit, pos)) {
                    _180 = hit;
                    end = hit;
                }
                sead::Matrix34f mtx = mActor->getMtx();
                mtx.m[0][3] = end.x;
                mtx.m[1][3] = end.y;
                mtx.m[2][3] = end.z;
                mActor->setMtx(mtx, false, true);
                if (auto* body = mActor->getMainBody())
                    body->setPosition(end);
                if (auto* set = mActor->getPhysics()->findBodyByName(sead::SafeString(*sub_71007A24BC()))) {
                    if (auto* body = set->getRigidBody(set->findBodyIndexByHavokName("AtkEnemyBody")))
                        body->setPosition(end);
                }
                dir = pos - end;
                dir.normalize();
            }
        }
        _e4 = dir;
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
        _170 = 3;
    } else {
        if (_170 != 0)
            return;
        ArrowShootMove::m33();
        if (!mActor)
            return;
        {
            const sead::Vector3f diff = mActor->getMtx().getTranslation() - _11c;
            if (diff.length() < *mSkyShootDist_s)
                return;
        }
        _174 = ksys::Timer(*mInterval_s, *mInterval_s);
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
        mActor->getMtx().getTranslation(_180);
        _170 = 1;
    }
}

bool ArrowSkyShootMove::sub_71000A6808(sead::Vector3f end, sead::Vector3f* out_hit,
                                       const sead::Vector3f& start) {
    ksys::phys::RayCastBodyQuery query(sub_7100738C18(mTargetActor_d, 0),
                                       ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    query.setStartAndEnd(start, end);
    bool hit = false;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(out_hit);
        hit = true;
    }
    return hit;
}

bool ArrowSkyShootMove::m34(sead::Vector3f* pos, bool* a, bool* b, sead::Vector3f* vel) {
    if (_170 == 3)
        return ArrowShootMove::m34(pos, a, b, vel);
    return false;
}

bool ArrowSkyShootMove::m40() {
    if (_170 != 3)
        return false;
    sead::Vector3f diff = _180;
    diff -= mActor->getMtx().getTranslation();
    return diff.length() >= *mAtRange_d * 2;
}

}  // namespace uking::action
