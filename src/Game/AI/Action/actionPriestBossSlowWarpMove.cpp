#include "Game/AI/Action/actionPriestBossSlowWarpMove.h"

namespace uking::action {

PriestBossSlowWarpMove::PriestBossSlowWarpMove(const InitArg& arg) : MoveBase(arg) {}

PriestBossSlowWarpMove::~PriestBossSlowWarpMove() = default;

bool PriestBossSlowWarpMove::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void PriestBossSlowWarpMove::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void PriestBossSlowWarpMove::leave_() {
    MoveBase::leave_();
}

void PriestBossSlowWarpMove::loadParams_() {
    MoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void PriestBossSlowWarpMove::calc_() {
    MoveBase::calc_();
}

}  // namespace uking::action
