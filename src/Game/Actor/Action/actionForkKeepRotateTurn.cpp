#include "Game/Actor/Action/actionForkKeepRotateTurn.h"
#include <cmath>
#include "KingSystem/Utils/MathUtil.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkKeepRotateTurn::ForkKeepRotateTurn(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkKeepRotateTurn::~ForkKeepRotateTurn() = default;

bool ForkKeepRotateTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkKeepRotateTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    const f32 angular_speed = actor->getAngVelocity().length();
    _5c.value = angular_speed;
    _5c.prev_value = angular_speed;
    sub_710073FA90(&_38, actor);
    mFlags.set(Flag::Changeable);
}

void ForkKeepRotateTurn::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkKeepRotateTurn::loadParams_() {
    getStaticParam(&mMinRotSpd_s, "MinRotSpd");
    getStaticParam(&mEndAngle_s, "EndAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkKeepRotateTurn::calc_() {
    const sead::Vector3f up = sead::Vector3f::ey;
    auto* actor = mActor;
    sub_710073FA94(&_38, actor);
    sead::Vector3f target = *mTargetPos_d;
    target -= mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&target, target, up);
    target.normalize();
    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, up);
    front.normalize();
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, target, sead::Vector3f::ey);
    if (actor->getAngVelocity().y * axis.y < 0.0f)
        angle = sead::Mathf::pi2() - angle;
    _5c.lerp(angle, 0.16f, _5c.value * 0.1f);
    f32 limit = *mMinRotSpd_s * 1.5f;
    limit = limit > _5c.value ? limit : _5c.value;
    limit = limit > angle ? limit : angle;
    _5c.clamp(*mMinRotSpd_s, limit);
    _5c.updateStats();
    sub_7100740464(&_38, target, up, sead::Vector3f::ey,
                    actor->getAngVelocity().y > 0.0f ? -1 : 1, true,
                    1.0f, _5c.value, 0.0f);
    sub_7100740F1C(_38, actor);
    front.y = 0.0f;
    front.normalize();
    target.y = 0.0f;
    target.normalize();
    if (front.dot(target) >= std::cos(*mEndAngle_s))
        setFinished();
}

}  // namespace uking::action
