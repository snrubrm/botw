#include "Game/Actor/Action/actionPlayerBeamMove.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

PlayerBeamMove::PlayerBeamMove(const InitArg& arg) : WindCutter(arg) {}

PlayerBeamMove::~PlayerBeamMove() = default;

void PlayerBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    WindCutter::enter_(params);
    _c8 = ksys::eft::searchAndEmitSLink(mActor, "Beam", false);
}

void PlayerBeamMove::leave_() {
    WindCutter::leave_();
    xlink::fade(_c8, -1);
}

void PlayerBeamMove::loadParams_() {
    WindCutter::loadParams_();
}

// NON_MATCHING: temporary effect handles and the hit transform use different stack slots.
void PlayerBeamMove::m32() {
    if (WindCutter::m33()) {
        Unk_71012419b4 handle;
        xlinkSearchAndEmit(mActor, "MasterBeamDisappear", 0, &handle);
        _c8.fade();
    } else if (hasAttackInfo(mActor)) {
        Unk_71012419b4 handle;
        xlinkSearchAndEmit(mActor, "MasterBeamDisappear", 2, &handle);
        _c8.fade();
    } else {
        sead::Vector3f position;
        if (!sub_710021DB44(&position)) {
            EmitAttackBase::m32();
            return;
        }
        Unk_71012419b4 handle;
        xlinkSearchAndEmit(mActor, "MasterBeamDisappear", 2, &handle);
        _c8.fade();
        sead::Matrix34f matrix(mActor->getMtx());
        matrix.setTranslation(position);
        if (auto* body = mActor->getMainBody())
            body->changePositionAndRotation(matrix, sead::Mathf::epsilon());
        auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkPlayerBody");
        if (body)
            body->changePositionAndRotation(matrix, sead::Mathf::epsilon());
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

// NON_MATCHING: velocity/position stack slots and initial scaling stores differ.
bool PlayerBeamMove::sub_710021DB44(sead::Vector3f* position) {
    if (!mActor)
        return false;
    auto* body = mActor->getMainBody();
    if (!body)
        return false;
    sead::Vector3f velocity;
    body->getLinearVelocity(&velocity);
    velocity *= 1.0f / 30.0f;
    velocity *= ksys::VFR::instance()->getDeltaFrame();
    sead::Vector3f from;
    body->getPosition(&from);
    const sead::Vector3f to = from + velocity;
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityTree);
    query.enableLayer(ksys::phys::ContactLayer::EntityObject);
    query.enableLayer(ksys::phys::ContactLayer::EntitySmallObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityAirWall);
    query.setStartAndEnd(from, to);
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(position);
        return true;
    }
    return false;
}

bool PlayerBeamMove::m33() {
    if (WindCutter::m33())
        return true;
    return hasAttackInfo(mActor);
}

f32 PlayerBeamMove::m34() {
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor))
        return bullet->_ca8;
    return WindCutter::m34();
}

int PlayerBeamMove::m37() {
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor))
        return bullet->_cac;
    return WindCutter::m37();
}

}  // namespace uking::action
