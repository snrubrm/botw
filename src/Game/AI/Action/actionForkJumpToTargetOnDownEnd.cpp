#include "Game/AI/Action/actionForkJumpToTargetOnDownEnd.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

ForkJumpToTargetOnDownEnd::ForkJumpToTargetOnDownEnd(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkJumpToTargetOnDownEnd::~ForkJumpToTargetOnDownEnd() = default;

bool ForkJumpToTargetOnDownEnd::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkJumpToTargetOnDownEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkJumpToTargetOnDownEnd::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkJumpToTargetOnDownEnd::loadParams_() {
    getStaticParam(&mParams.mAngleDir_s, "AngleDir");
    getStaticParam(&mParams.mJumpDist_s, "JumpDist");
    getStaticParam(&mParams.mJumpHeight_s, "JumpHeight");
    getStaticParam(&mParams.mLimitSpeed_s, "LimitSpeed");
    getStaticParam(&mParams.mEndGrSpeed_s, "EndGrSpeed");
    getStaticParam(&mParams.mJumpMinDist_s, "JumpMinDist");
    getStaticParam(&mParams.mOnGround_s, "OnGround");
    getStaticParam(&mParams.mIsBasisByTarget_s, "IsBasisByTarget");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void ForkJumpToTargetOnDownEnd::calc_() {
    if (_80) {
        _80 = false;
        return;
    }

    auto* actor = mActor;
    if (auto* controller = actor->getCharacterController()) {
        controller->sub_7100F5E7F0(_74.value * 30.0f);
        sub_710072C1B4(controller, _68);
    }

    if (actor->getVelocity().y > *mParams.mEndGrSpeed_s)
        _81 = true;
    if ((_81 && actor->getVelocity().y <= *mParams.mEndGrSpeed_s) || isBgGroundHit(actor, false))
        setFinished();
}

}  // namespace uking::action
