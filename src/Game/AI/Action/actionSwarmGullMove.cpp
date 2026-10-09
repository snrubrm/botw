#include "Game/AI/Action/actionSwarmGullMove.h"

namespace uking::action {

SwarmGullMove::SwarmGullMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwarmGullMove::~SwarmGullMove() {
    _1b0.freeBuffer();
}

bool SwarmGullMove::init_(sead::Heap* heap) {
    return _1b0.tryAllocBuffer(3, heap);
}

void SwarmGullMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwarmGullMove::leave_() {
    sub_71002868BC();
    for (auto& gull : _70) {
        if (gull._0.isAllocatedOrFailed()) {
            gull._0.deleteProc();
            if (gull._10) {
                sub_7100287830(&gull);
                gull._10->m10();
            }
        }
    }
}

void SwarmGullMove::loadParams_() {
    getStaticParam(&mParams.mASName_s, "ASName");
    getMapUnitParam(&mParams.mSubUnitNum_m, "SubUnitNum");
    getMapUnitParam(&mParams.mCreateMaxRadius_m, "CreateMaxRadius");
    getMapUnitParam(&mParams.mCreateMinRadius_m, "CreateMinRadius");
    getMapUnitParam(&mParams.mCreateHeightRange_m, "CreateHeightRange");
    getMapUnitParam(&mParams.mRoundMaxRadius_m, "RoundMaxRadius");
    getMapUnitParam(&mParams.mRoundMinRadius_m, "RoundMinRadius");
    getMapUnitParam(&mParams.mCrySoundIntervalMin_m, "CrySoundIntervalMin");
    getMapUnitParam(&mParams.mCrySoundIntervalMax_m, "CrySoundIntervalMax");
}

void SwarmGullMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
