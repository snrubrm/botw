#include "Game/AI/Action/actionLandTeleport.h"
#include "math/seadMathCalcCommon.h"
#include "random/seadGlobalRandom.h"

namespace uking::action {

LandTeleport::LandTeleport(const InitArg& arg) : TeleportBase(arg) {}

LandTeleport::~LandTeleport() = default;

bool LandTeleport::init_(sead::Heap* heap) {
    return TeleportBase::init_(heap);
}

void LandTeleport::enter_(ksys::act::ai::InlineParamPack* params) {
    TeleportBase::enter_(params);
}

void LandTeleport::leave_() {
    TeleportBase::leave_();
}

void LandTeleport::loadParams_() {
    TeleportBase::loadParams_();
    getStaticParam(&mDistXZ_s, "DistXZ");
    getStaticParam(&mDistY_s, "DistY");
    getStaticParam(&mSearchClosestPointRadius_s, "SearchClosestPointRadius");
    getStaticParam(&mIsNormalizeAxisY_s, "IsNormalizeAxisY");
}

void LandTeleport::calc_() {
    TeleportBase::calc_();
}

void LandTeleport::m40() {
    _a4 = sead::Vector3f::zero;
    const f32 angle = s32(sead::GlobalRandom::instance()->getU32(360)) / 360.0f * sead::Mathf::pi2();
    _a4.x = sead::Mathf::cos(angle) * *mDistXZ_s;
    _a4.z = sead::Mathf::sin(angle) * *mDistXZ_s;
    _a4.y = 1.0f;
}

}  // namespace uking::action
