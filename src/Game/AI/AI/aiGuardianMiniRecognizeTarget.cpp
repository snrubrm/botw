#include "Game/AI/AI/aiGuardianMiniRecognizeTarget.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GuardianMiniRecognizeTarget::GuardianMiniRecognizeTarget(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GuardianMiniRecognizeTarget::~GuardianMiniRecognizeTarget() = default;

void GuardianMiniRecognizeTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000)) {
        changeChild("発見");
        return;
    }
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    changeChild("未発見");
}

bool GuardianMiniRecognizeTarget::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void GuardianMiniRecognizeTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniRecognizeTarget::loadParams_() {}

void GuardianMiniRecognizeTarget::calc_() {
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("未発見")) {
        changeChild("発見");
        return;
    }

    child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("発見")) {
        if (getCurrentChild()->isFinished())
            setFinished();
        else
            setFailed();
    }
}

}  // namespace uking::ai
