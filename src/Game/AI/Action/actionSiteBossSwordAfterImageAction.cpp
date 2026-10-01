#include "Game/AI/Action/actionSiteBossSwordAfterImageAction.h"

namespace uking::action {

SiteBossSwordAfterImageAction::SiteBossSwordAfterImageAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossSwordAfterImageAction::~SiteBossSwordAfterImageAction() = default;

bool SiteBossSwordAfterImageAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossSwordAfterImageAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossSwordAfterImageAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossSwordAfterImageAction::loadParams_() {
    getMapUnitParam(&mCount_m, "Count");
    getAITreeVariable(&mSiteBossSwordAfterImageUnit_a, "SiteBossSwordAfterImageUnit");
}

void SiteBossSwordAfterImageAction::calc_() {
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
