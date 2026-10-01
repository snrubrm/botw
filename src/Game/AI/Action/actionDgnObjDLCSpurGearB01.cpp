#include "Game/AI/Action/actionDgnObjDLCSpurGearB01.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace uking::action {

DgnObjDLCSpurGearB01::DgnObjDLCSpurGearB01(const InitArg& arg) : GearRotate(arg) {}

DgnObjDLCSpurGearB01::~DgnObjDLCSpurGearB01() = default;

bool DgnObjDLCSpurGearB01::init_(sead::Heap* heap) {
    return GearRotate::init_(heap);
}

void DgnObjDLCSpurGearB01::enter_(ksys::act::ai::InlineParamPack* params) {
    GearRotate::enter_(params);
    _78 = _50;
}

void DgnObjDLCSpurGearB01::leave_() {
    GearRotate::leave_();
}

void DgnObjDLCSpurGearB01::loadParams_() {
    GearRotate::loadParams_();
}

void DgnObjDLCSpurGearB01::calc_() {
    GearRotate::calc_();
    if (ksys::phys::System::instance()->isPaused())
        _50 = _78;
    _78 = _50;
}

}  // namespace uking::action
