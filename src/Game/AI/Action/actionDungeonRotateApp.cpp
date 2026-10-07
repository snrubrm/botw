#include "Game/AI/Action/actionDungeonRotateApp.h"
#include "KingSystem/System/VFR.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

DungeonRotateApp::DungeonRotateApp(const InitArg& arg) : DungeonRotateBase(arg) {}

DungeonRotateApp::~DungeonRotateApp() = default;

bool DungeonRotateApp::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DungeonRotateApp::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
    _d8 = sead::Mathf::deg2rad(*mDynTargetAng_d);
    switch (*mRotDirType_s) {
    case 1:
        if (_d8 - _80 > 0.0f)
            _d8 += -2 * sead::Mathf::pi();
        break;
    case 2:
        if (_d8 - _80 < 0.0f)
            _d8 += 2 * sead::Mathf::pi();
        break;
    }
}

void DungeonRotateApp::leave_() {
    DungeonRotateBase::leave_();
}

void DungeonRotateApp::loadParams_() {
    DungeonRotateBase::loadParams_();
    getStaticParam(&mRotDirType_s, "RotDirType");
    getDynamicParam(&mDynTargetAng_d, "DynTargetAng");
}

void DungeonRotateApp::calc_() {
    DungeonRotateBase::calc_();
    m35();
    const bool finished = ksys::VFR::chase(&_80, _d8, _84);
    if (_90) {
        ui::sub_7100A9D244(_80);
        const sead::Vector3f rotation = _70 * _80;
        sub_71000FCCA4(&rotation, _d8 < _80);
    }
    if (finished) {
        sub_71000FD51C();
        setFinished();
    }
}

}  // namespace uking::action
