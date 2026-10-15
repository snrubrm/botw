#include "Game/Actor/Action/actionRemainsWaterBulletWait.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

RemainsWaterBulletWait::RemainsWaterBulletWait(const InitArg& arg)
    : RemainsWaterBulletAction(arg) {}

RemainsWaterBulletWait::~RemainsWaterBulletWait() = default;

bool RemainsWaterBulletWait::init_(sead::Heap* heap) {
    return RemainsWaterBulletAction::init_(heap);
}

void RemainsWaterBulletWait::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsWaterBulletAction::enter_(params);
    mFlags.set(Flag::Changeable);
}

void RemainsWaterBulletWait::leave_() {
    RemainsWaterBulletAction::leave_();
}

void RemainsWaterBulletWait::loadParams_() {
    RemainsWaterBulletAction::loadParams_();
    getStaticParam(&mMaxChaseAngle_s, "MaxChaseAngle");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mChaseRate_s, "ChaseRate");
    getMapUnitParam(&mRemainsWaterBulletAngle_m, "RemainsWaterBulletAngle");
    getMapUnitParam(&mRemainsWaterBulletOffset_m, "RemainsWaterBulletOffset");
}

void RemainsWaterBulletWait::calc_() {
    RemainsWaterBulletAction::calc_();
}

// NON_MATCHING: target/position stack slots and velocity scaling stores differ.
void RemainsWaterBulletWait::m32() {
    auto* body = mActor->getMainBody();
    if (!body || !body->isAddedToWorld())
        return;
    sead::Vector3f target;
    sub_71002325BC(&target);
    if (target.isNan())
        target = mActor->getMtx().getTranslation();
    sead::Vector3f position;
    sead::Vector3f velocity;
    body->getPosition(&position);
    body->getLinearVelocity(&velocity);
    if (velocity.isNan())
        velocity.set(0.0f, 0.0f, 0.0f);
    else
        velocity *= 1.0f / 30.0f;
    sead::Vector3f direction = target - position;
    if (direction.length() > 0.0f) {
        const f32 length = direction.normalize();
        direction *= length > *mMaxSpeed_s ? *mMaxSpeed_s : length;
    }
    ksys::VFR::lerp(&velocity, direction, *mChaseRate_s);
    body->setLinearVelocity(velocity * 30.0f, sead::Mathf::epsilon());
}

// NON_MATCHING: transform-vector registers, angle temporaries and accessor teardown branches differ.
void RemainsWaterBulletWait::sub_71002325BC(sead::Vector3f* position) {
    if (!position)
        return;
    const sead::Vector3f translation = mActor->getMtx().getTranslation();
    *position = translation;
    auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor);
    ksys::act::acc::PlayerBase player;
    if (!bullet || !player.getPlayerFromPlayerInfo())
        return;
    ksys::act::ActorLinkConstDataAccess parent;
    if (!ksys::act::acquireActor(&bullet->_bd0._0, &parent))
        return;
    const sead::Matrix34f parent_matrix(parent.getActorMtx());
    sead::Matrix34f inverse;
    inverse.setInverse(parent_matrix);
    const sead::Vector3f player_position = player.getActorMtx().getTranslation();
    const sead::Vector3f parent_position = parent_matrix.getTranslation();
    sead::Vector3f front = parent_matrix.getBase(2);
    front.normalize();
    front.y = 0.0f;
    front.normalize();
    sead::Vector3f player_direction = player_position - parent_position;
    player_direction.rotate(inverse);
    player_direction.z *= mRemainsWaterBulletOffset_m->x / mRemainsWaterBulletOffset_m->z;
    player_direction.rotate(parent_matrix);
    player_direction.y = 0.0f;
    player_direction.normalize();
    sead::Vector3f axis;
    f32 angle = 0.0f;
    ksys::util::sub_71011EEB08(&axis, &angle, front, player_direction, sead::Vector3f::ey);
    angle = axis.y * angle + *mRemainsWaterBulletAngle_m;
    sead::Vector3f direction = translation - parent_position;
    direction.rotate(inverse);
    direction.z *= mRemainsWaterBulletOffset_m->x / mRemainsWaterBulletOffset_m->z;
    direction.rotate(parent_matrix);
    direction.y = 0.0f;
    direction.normalize();
    f32 current_angle = 0.0f;
    ksys::util::sub_71011EEB08(&axis, &current_angle, direction, player_direction,
                              sead::Vector3f::ey);
    current_angle = axis.y * current_angle + *mRemainsWaterBulletAngle_m;
    if (sead::Mathf::abs(current_angle) > *mMaxChaseAngle_s) {
        const f32 sign = current_angle >= 0.0f ? 1.0f : -1.0f;
        angle = *mMaxChaseAngle_s * sign + (angle - current_angle);
    }
    position->y = mRemainsWaterBulletOffset_m->y;
    position->x = mRemainsWaterBulletOffset_m->x * std::sin(angle);
    position->z = mRemainsWaterBulletOffset_m->z * std::cos(angle);
    position->setMul(parent_matrix, *position);
}

}  // namespace uking::action
