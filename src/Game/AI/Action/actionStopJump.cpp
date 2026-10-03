#include "Game/AI/Action/actionStopJump.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

StopJump::StopJump(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

StopJump::~StopJump() = default;

bool StopJump::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void StopJump::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    _58 = 0;
}

void StopJump::leave_() {
    ActionWithPosAngReduce::leave_();
}

void StopJump::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpLoopAS_s, "JumpLoopAS");
    getStaticParam(&mLandingAS_s, "LandingAS");
}

// NON_MATCHING: the SafeString `this` register setup of the second playAS (`ldr x8, [x0, #0x48]!`)
void StopJump::calc_() {
    ActionWithPosAngReduce::calc_();
    if (isFinished() || isFailed())
        return;

    switch (_58) {
    case 0:
        if (isBgGroundHit(mActor, false)) {
            if (auto* controller = mActor->getCharacterController()) {
                controller->sub_7100F5EF08(true);
                controller->sub_7100F62B70(*mJumpHeight_s);
            }
            playAS(mJumpLoopAS_s.cstr(), false, 0, 0, -1.0f);
            _58 = 1;
        }
        break;
    case 1:
        if (isBgGroundHit(mActor, false) || sub_71005E1064(mActor)) {
            if (mLandingAS_s.isEmpty()) {
                setFinished();
            } else {
                playAS(mLandingAS_s.cstr(), false, 0, 0, -1.0f);
                _58 = 2;
            }
        }
        break;
    case 2:
        if (isFinishedAS(0, 0))
            setFinished();
        break;
    }
}

bool StopJump::isFinished() const {
    if (ksys::act::ai::Action::isFinished())
        return true;
    if (_58 != 1 || !mLandingAS_s.isEmpty())
        return false;
    return isBgGroundHit(mActor, false) || sub_71005E1064(mActor);
}

}  // namespace uking::action
