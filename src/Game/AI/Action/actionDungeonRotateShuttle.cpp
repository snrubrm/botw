#include "Game/AI/Action/actionDungeonRotateShuttle.h"

namespace uking::action {

DungeonRotateShuttle::DungeonRotateShuttle(const InitArg& arg) : DungeonRotateBase(arg) {}

DungeonRotateShuttle::~DungeonRotateShuttle() = default;

bool DungeonRotateShuttle::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DungeonRotateShuttle::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
    const f32 angle = sead::Mathf::deg2rad(*mTiltAngle_m);
    _d8 = _80 + (*mRotDir_s == 0 ? -angle : angle);
}

void DungeonRotateShuttle::leave_() {
    DungeonRotateBase::leave_();
}

void DungeonRotateShuttle::loadParams_() {
    DungeonRotateBase::loadParams_();
    getStaticParam(&mRotDir_s, "RotDir");
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
}

void DungeonRotateShuttle::calc_() {
    DungeonRotateBase::calc_();
}

}  // namespace uking::action
