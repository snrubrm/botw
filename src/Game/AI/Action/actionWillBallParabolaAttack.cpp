#include "Game/AI/Action/actionWillBallParabolaAttack.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

WillBallParabolaAttack::WillBallParabolaAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WillBallParabolaAttack::~WillBallParabolaAttack() = default;

bool WillBallParabolaAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: vector arithmetic, capped speed and actor receiver use different registers
// and scheduling around the solver and random calls.
void WillBallParabolaAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f start;
    mActor->getMtx().getTranslation(start);
    sead::Vector3f target = *mTargetPos_d;
    sead::Vector3f direction = target - start;
    if (direction.normalize() < *mMinMoveXZ_s) {
        direction *= *mMinMoveXZ_s;
        target = direction + start;
        direction.normalize();
    }
    if (auto* body = mActor->getMainBody()) {
        _48 = body->getGravityFactor();
        body->setGravityFactor(*mGravityScale_s);
        sead::BoundBox3f bounds;
        body->getAabbInLocal(&bounds);
        target.y += bounds.getSizeY() * 0.5f + 1.0f;
    }
    const sead::Vector3f gravity = getGravity(mActor) * (1.0f / 900.0f);
    f32 speed;
    f32 time;
    if (!sub_710072CD88(*mMaxHeight_s, &speed, &time, &start, &target, &gravity))
        speed = *mMaxSpeed_s;
    direction.normalize();
    const f32 capped_speed = speed > *mMaxSpeed_s ? *mMaxSpeed_s : speed;
    const f32 up_speed = sub_710072D068(&gravity, *mMaxHeight_s);
    const f32 rate = sead::GlobalRandom::instance()->getF32Range(0.95f, 1.0f);
    const sead::Vector3f velocity{direction.x * capped_speed * rate, up_speed * rate,
                                direction.z * capped_speed * rate};
    ksys::act::sub_7100EE5980(mActor, velocity);
    _4c = false;
}

void WillBallParabolaAttack::leave_() {
    if (auto* body = mActor->getMainBody())
        body->setGravityFactor(_48);
}

void WillBallParabolaAttack::loadParams_() {
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mMaxHeight_s, "MaxHeight");
    getStaticParam(&mMinMoveXZ_s, "MinMoveXZ");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mGravityScale_s, "GravityScale");
}

void WillBallParabolaAttack::calc_() {
    auto* actor = mActor;
    if (actor->getVelocity().y < 0.0f)
        _4c = true;
    else if (!_4c)
        return;
    if (isBgGroundHit(actor, false))
        setFinished();
}

}  // namespace uking::action
