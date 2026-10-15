#include "Game/Actor/Action/actionDgnObj_DLC_DungeonRotate.h"
#include <xlink2/xlink2HandleSLink.h>
#include <math/seadQuat.h>
#include "Game/Actor/actSoundProxy.h"
#include "Game/gameGearMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

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

void DgnObj_DLC_DungeonRotate::sub_71000EE43C() {
    auto* gear = GearMgr::instance();
    if (gear && !(gear->_10a4 & 8))
        return;
    auto* manager = ksys::snd::SoundMgr::instance()->_a0;
    auto* proxy = manager->sub_710105A830(sub_71000FC4EC());
    if (proxy) {
        xlink2::HandleSLink handle;
        if (_b4)
            proxy->sub_710105A10C("StartActionCW", &handle);
        else
            proxy->sub_710105A10C("StartActionCCW", &handle);
        if (!handle.isActive())
            proxy->sub_710105A10C("StartAction", &handle);
    } else {
        xlink2::HandleSLink handle;
        if (_b4)
            ksys::eft::sub_710105DDB8(mActor, "StartActionCW", &handle);
        else
            ksys::eft::sub_710105DDB8(mActor, "StartActionCCW", &handle);
        if (!handle.isActive())
            ksys::eft::sub_710105DDB8(mActor, "StartAction", &handle);
    }
}

// NON_MATCHING: Clang outlines the existing quaternion-to-RPY conversion.
void DgnObj_DLC_DungeonRotate::calc_() {
    DungeonRotateBase::calc_();
    if (!_90)
        return;
    auto* gear = GearMgr::instance();
    if (!gear || !gear->sub_7100669B48())
        return;
    _80 = (gear->_1098 - *mRotationOffset_a) * _e4 * _e0 + _e8;
    _80 = ksys::util::sub_71011EF0CC(_80);
    _b8 = gear->_10cc;
    sead::Quatf quaternion;
    quaternion.setAxisRadian(_70, _80);
    sead::Vector3f rotation;
    quaternion.calcRPY(rotation);
    sub_71000FCCA4(&rotation, _84 < 0.0f);
    if (gear->_10dd)
        sub_71000EE43C();
}

}  // namespace uking::action
