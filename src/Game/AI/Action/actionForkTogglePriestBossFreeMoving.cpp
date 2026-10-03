#include "Game/AI/Action/actionForkTogglePriestBossFreeMoving.h"
#include "Game/AI/aiUnk_710071E0D8.h"

namespace uking::action {

ForkTogglePriestBossFreeMoving::ForkTogglePriestBossFreeMoving(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkTogglePriestBossFreeMoving::~ForkTogglePriestBossFreeMoving() = default;

void ForkTogglePriestBossFreeMoving::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710071E0D8(*mSetFreeMoving_s, mActor);
    mFlags.set(Flag::Changeable);
    setFinished();
}

void ForkTogglePriestBossFreeMoving::loadParams_() {
    getStaticParam(&mSetFreeMoving_s, "SetFreeMoving");
}

}  // namespace uking::action
