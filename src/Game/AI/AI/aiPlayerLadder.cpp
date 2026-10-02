#include "Game/AI/AI/aiPlayerLadder.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PlayerLadder::PlayerLadder(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerLadder::~PlayerLadder() = default;

bool PlayerLadder::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerLadder::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerLadder::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
}

void PlayerLadder::loadParams_() {
    getStaticParam(&mLadderToClimbTime_s, "LadderToClimbTime");
}

bool PlayerLadder::isChangeable() const {
    return isCurrentChild("登り終わり") && getCurrentChild()->isChangeable();
}

}  // namespace uking::ai
