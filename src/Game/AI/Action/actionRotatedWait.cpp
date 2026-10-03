#include "Game/AI/Action/actionRotatedWait.h"

namespace uking::action {

RotatedWait::RotatedWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RotatedWait::~RotatedWait() = default;

bool RotatedWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RotatedWait::enter_(ksys::act::ai::InlineParamPack* params) {
    switch (*mRotAxis_m) {
    case 0:
        _38.set(sead::Vector3f::ex);
        break;
    case 1:
        _38.set(sead::Vector3f::ey);
        break;
    case 2:
        _38.set(sead::Vector3f::ez);
        break;
    }
    mFlags.set(Flag::Changeable);
    setFinished();
}

void RotatedWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void RotatedWait::loadParams_() {
    getMapUnitParam(&mRotAxis_m, "RotAxis");
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
}

void RotatedWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
