#include "Game/AI/Action/actionRideHorseAction.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

RideHorseAction::RideHorseAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RideHorseAction::~RideHorseAction() = default;

bool RideHorseAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RideHorseAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* info = mActor->getPlayerRideInfo())
        info->sub_7100E7C054(mHorse_d);
    setFinished();
}

void RideHorseAction::loadParams_() {
    getDynamicParam(&mHorse_d, "Horse");
}

}  // namespace uking::action
