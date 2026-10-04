#include "Game/AI/Action/actionAnimTimingAttackMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

AnimTimingAttackMove::AnimTimingAttackMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimTimingAttackMove::~AnimTimingAttackMove() = default;

bool AnimTimingAttackMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimTimingAttackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    sub_71007A2C30(mActor, mRigidBodyName_s, nullptr);
    _70 = 0;
    _71 = 0;
    _72 = false;
    if (auto* nav = mActor->m45()) {
        const bool value = u16(nav->_2a4.load()) != 0x17;
        _71 = value;
        _72 = value;
    }
}

void AnimTimingAttackMove::leave_() {
    sub_71007A2D7C(mActor, mRigidBodyName_s);
}

void AnimTimingAttackMove::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mIsRound_s, "IsRound");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnimTimingAttackMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
