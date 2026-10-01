#include "Game/AI/AI/aiDeadOrOtherState.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

DeadOrOtherState::DeadOrOtherState(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool DeadOrOtherState::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DeadOrOtherState::enter_(ksys::act::ai::InlineParamPack* params) {
    const auto* life = mActor->getLife();
    if (life && *life <= 0)
        changeChild("死亡");
    else
        changeChild("その他");
}

void DeadOrOtherState::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DeadOrOtherState::loadParams_() {}

bool DeadOrOtherState::isFinished() const {
    if (isCurrentChild("死亡"))
        return ActionBase::isFinished();
    return ActionBase::isFinished() || getCurrentChild()->isFinished();
}

bool DeadOrOtherState::isFailed() const {
    if (isCurrentChild("死亡"))
        return ActionBase::isFailed();
    return ActionBase::isFailed() || getCurrentChild()->isFailed();
}

}  // namespace uking::ai
