#include "Game/AI/Action/actionDungeonRotateGyro.h"
#include <xlink2/xlink2Handle.h>

namespace uking::action {

DungeonRotateGyro::DungeonRotateGyro(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DungeonRotateGyro::~DungeonRotateGyro() {
    if (_108) {
        delete _108;
        _108 = nullptr;
    }
}

bool DungeonRotateGyro::init_(sead::Heap* heap) {
    _108 = new (heap) xlink2::Handle;
    return true;
}

void DungeonRotateGyro::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DungeonRotateGyro::leave_() {
    ksys::act::ai::Action::leave_();
}

void DungeonRotateGyro::loadParams_() {
    getStaticParam(&mSlerpRatio_s, "SlerpRatio");
    getStaticParam(&mIsUseInstParamSlerpRatio_s, "IsUseInstParamSlerpRatio");
    getMapUnitParam(&mInitDgnPriority_m, "InitDgnPriority");
    getMapUnitParam(&mGyroSlerpRatio_m, "GyroSlerpRatio");
}

void DungeonRotateGyro::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
