#include "Game/AI/AI/aiPlayerSit.h"
#include "Game/AI/aiUnk_710087CE34.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PlayerSit::PlayerSit(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerSit::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerSit::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    sub_710087CE34(mActor);
    if (hasPendingChildChange())
        changeChild(mPendingChildIdx);
    else
        changeChild("開始");
}

void PlayerSit::calc_() {
    if (handlePendingChildChange())
        return;

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("開始"))
        changeChild("待機");
    else if (isCurrentChild("待機"))
        changeChild("終了");
}

void PlayerSit::leave_() {
    sub_710087CE90(mActor);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
}

bool PlayerSit::isFinished() const {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("終了"))
            return true;
    }
    return false;
}

}  // namespace uking::ai
