#include "Game/AI/Action/actionForkFlyToTargetDirect.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkFlyToTargetDirect::ForkFlyToTargetDirect(const InitArg& arg) : FreeMovingAction(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkFlyToTargetDirect::~ForkFlyToTargetDirect() {
    ;
}

bool ForkFlyToTargetDirect::init_(sead::Heap* heap) {
    return FreeMovingAction::init_(heap);
}

void ForkFlyToTargetDirect::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMovingAction::enter_(params);
    const f32 speed = mActor->getVelocity().length();
    _58.value = speed;
    _58.prev_value = speed;
    mFlags.set(Flag::Changeable);
}

void ForkFlyToTargetDirect::leave_() {
    FreeMovingAction::leave_();
    if (*mOnEndForceStop_s)
        ksys::act::sub_7100EE5980(mActor, sead::Vector3f::zero);
}

void ForkFlyToTargetDirect::loadParams_() {
    FreeMovingAction::loadParams_();
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mMoveSpd_s, "MoveSpd");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mOnEndForceStop_s, "OnEndForceStop");
    getStaticParam(&mOnGround_s, "OnGround");
}

// NON_MATCHING: vector temporaries and interpolation registers differ.
void ForkFlyToTargetDirect::calc_() {
    FreeMovingAction::calc_();
    const f32 speed = *mMoveSpd_s > _58.value ? *mMoveSpd_s : _58.value;
    auto* actor = mActor;
    _58.lerp(*mMoveSpd_s, 0.12f, speed * 0.2f, speed * 0.05f);
    _58.updateStats();
    auto target = *mTargetPos_d;
    const auto& actor_matrix = actor->getMtx();
    const sead::Vector3f position{actor_matrix(0, 3), actor_matrix(1, 3), actor_matrix(2, 3)};
    if (*mOnGround_s) {
        auto ray_start = target;
        ray_start.y = position.y + 1.0f;
        if (!somePositionCalc(&target, ray_start, -sead::Vector3f::ey, 10.0f))
            target = *mTargetPos_d;
    }
    auto direction = target - position;
    const f32 distance = direction.normalize();
    const auto next_position = distance < _58.value ? target : position + direction * _58.value;
    ksys::act::sub_7100EE57FC(actor, next_position);
    if (distance - _58.value < *mFinRadius_s)
        setFinished();
}

}  // namespace uking::action
