#include "Game/AI/Action/actionDungeonRotateInOrder.h"

namespace uking::action {

DungeonRotateInOrder::DungeonRotateInOrder(const InitArg& arg) : DungeonRotateBase(arg) {}

bool DungeonRotateInOrder::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DungeonRotateInOrder::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
    const f32 angle = sead::Mathf::deg2rad(*mTiltAngle_m);
    _d8 = _80 + (*mDgnRotDir_m == 0 ? -angle : angle);
}

void DungeonRotateInOrder::leave_() {
    DungeonRotateBase::leave_();
}

void DungeonRotateInOrder::loadParams_() {
    DungeonRotateBase::loadParams_();
    getMapUnitParam(&mDgnRotDir_m, "DgnRotDir");
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
}

void DungeonRotateInOrder::calc_() {
    DungeonRotateBase::calc_();
}

}  // namespace uking::action
