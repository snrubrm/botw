#include "Game/AI/Action/actionSandwormJumpTackle.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

SandwormJumpTackle::SandwormJumpTackle(const InitArg& arg) : JumpTackle(arg) {}

SandwormJumpTackle::~SandwormJumpTackle() = default;

bool SandwormJumpTackle::init_(sead::Heap* heap) {
    return JumpTackle::init_(heap);
}

void SandwormJumpTackle::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpTackle::enter_(params);
}

void SandwormJumpTackle::leave_() {
    JumpTackle::leave_();
}

void SandwormJumpTackle::loadParams_() {
    JumpTackle::loadParams_();
    getStaticParam(&mPosReduceRate_s, "PosReduceRate");
    getStaticParam(&mGravityScale_s, "GravityScale");
    getStaticParam(&mAtkColName_s, "AtkColName");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void SandwormJumpTackle::calc_() {
    JumpTackle::calc_();
}

bool SandwormJumpTackle::m34() const {
    if (!isFinishedAS(0, 0))
        return false;
    if (JumpTackle::m34())
        return true;
    auto* controller = mActor->getCharacterController();
    if (controller && controller->sub_7100F5F0E4() == ksys::act::MotionType::_0)
        return true;
    return false;
}

}  // namespace uking::action
