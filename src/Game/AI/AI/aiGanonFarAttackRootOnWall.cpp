#include "Game/AI/AI/aiGanonFarAttackRootOnWall.h"

namespace uking::ai {

GanonFarAttackRootOnWall::GanonFarAttackRootOnWall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonFarAttackRootOnWall::~GanonFarAttackRootOnWall() = default;

bool GanonFarAttackRootOnWall::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonFarAttackRootOnWall::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = 0;
    sub_71003E8884();
}

void GanonFarAttackRootOnWall::leave_() {
    sub_71003E9150();
}

void GanonFarAttackRootOnWall::loadParams_() {
    getStaticParam(&mPillarMax_s, "PillarMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mViewPos_d, "ViewPos");
}

}  // namespace uking::ai
