#include "Game/AI/Action/actionDungeonRotateInOrder.h"
#include "KingSystem/System/VFR.h"

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
    m35();
    const bool finished = ksys::VFR::chase(&_80, _d8, _84);
    if (_90) {
        const sead::Vector3f rotation = _70 * _80;
        sub_71000FCCA4(&rotation, _d8 < _80);
    }
    if (finished) {
        sub_71000FD51C();
        setFinished();
    }
}

}  // namespace uking::action
