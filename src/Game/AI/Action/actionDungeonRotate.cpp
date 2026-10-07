#include "Game/AI/Action/actionDungeonRotate.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

DungeonRotate::DungeonRotate(const InitArg& arg) : DungeonRotateBase(arg) {}

DungeonRotate::~DungeonRotate() = default;

bool DungeonRotate::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DungeonRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
    mFlags.set(Flag::Changeable);
}

void DungeonRotate::leave_() {
    DungeonRotateBase::leave_();
    sub_71000FD51C();
}

void DungeonRotate::loadParams_() {
    DungeonRotateBase::loadParams_();
    getMapUnitParam(&mDgnRotDir_m, "DgnRotDir");
}

void DungeonRotate::calc_() {
    DungeonRotateBase::calc_();
    m35();
    const f32 delta = _84 * ksys::VFR::instance()->getDeltaFrame();
    _80 += *mDgnRotDir_m == 0 ? -delta : delta;
    _80 = ksys::util::sub_71011EF0CC(_80);
    if (_90) {
        const sead::Vector3f rotation = _70 * _80;
        sub_71000FCCA4(&rotation, _84 < 0.0f);
    }
}

}  // namespace uking::action
