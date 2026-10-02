#include "Game/AI/Action/actionDungeonRotateCont.h"

namespace uking::action {

DungeonRotateCont::DungeonRotateCont(const InitArg& arg) : DungeonRotateBase(arg) {}

DungeonRotateCont::~DungeonRotateCont() = default;

bool DungeonRotateCont::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DungeonRotateCont::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
    const f32 angle = sead::Mathf::deg2rad(*mTiltAngle_m);
    _e0 = _80 + (*mDgnRotDir_m == 0 ? -angle : angle);
}

void DungeonRotateCont::leave_() {
    DungeonRotateBase::leave_();
}

void DungeonRotateCont::loadParams_() {
    DungeonRotateBase::loadParams_();
    getMapUnitParam(&mDgnRotDir_m, "DgnRotDir");
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
    getAITreeVariable(&mIsContinueRotateOrMove_a, "IsContinueRotateOrMove");
}

void DungeonRotateCont::calc_() {
    DungeonRotateBase::calc_();
}

}  // namespace uking::action
