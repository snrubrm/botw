#include "Game/AI/Action/actionDgnObj_DLC_DungeonRotate.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

DgnObj_DLC_DungeonRotate::DgnObj_DLC_DungeonRotate(const InitArg& arg) : DungeonRotateBase(arg) {}

DgnObj_DLC_DungeonRotate::~DgnObj_DLC_DungeonRotate() = default;

bool DgnObj_DLC_DungeonRotate::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DgnObj_DLC_DungeonRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
    const f32 gear_ratio = *mGearRatio_m;
    _e0 = gear_ratio > 0.0f ? 1.0f / gear_ratio : 0.0f;
    _e4 = *mIsClockWiseRotation_m ? 1.0f : -1.0f;
    _e8 = _80;
    sub_71000EE43C();
    mFlags.set(Flag::Changeable);
}

void DgnObj_DLC_DungeonRotate::leave_() {
    DungeonRotateBase::leave_();
}

void DgnObj_DLC_DungeonRotate::loadParams_() {
    DungeonRotateBase::loadParams_();
    getMapUnitParam(&mGearRatio_m, "GearRatio");
    getMapUnitParam(&mIsClockWiseRotation_m, "IsClockWiseRotation");
    getAITreeVariable(&mRotationOffset_a, "RotationOffset");
}

void DgnObj_DLC_DungeonRotate::calc_() {
    DungeonRotateBase::calc_();
}

}  // namespace uking::action
