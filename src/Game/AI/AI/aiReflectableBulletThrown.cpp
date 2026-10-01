#include "Game/AI/AI/aiReflectableBulletThrown.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ReflectableBulletThrown::ReflectableBulletThrown(const InitArg& arg) : ReflectableThrown(arg) {}

ReflectableBulletThrown::~ReflectableBulletThrown() = default;

bool ReflectableBulletThrown::init_(sead::Heap* heap) {
    return ReflectableThrown::init_(heap);
}

void ReflectableBulletThrown::enter_(ksys::act::ai::InlineParamPack* params) {
    ReflectableThrown::enter_(params);
}

void ReflectableBulletThrown::calc_() {
    ReflectableThrown::calc_();
}

void ReflectableBulletThrown::leave_() {
    ReflectableThrown::leave_();
}

void ReflectableBulletThrown::loadParams_() {
    ReflectableThrown::loadParams_();
    getDynamicParam(&mPower_d, "Power");
    getDynamicParam(&mIsShootByPlayer_d, "IsShootByPlayer");
    getDynamicParam(&mTargetDir_d, "TargetDir");
    getStaticParam(&mReclectSpd_s, "ReclectSpd");
}

void ReflectableBulletThrown::m34() {
    ksys::act::ai::InlineParamPack params;
    params.addFloat(*mPower_d, "Power", -1);
    params.addVec3(*mTargetDir_d, "TargetDir", -1);
    params.addBool(*mIsShootByPlayer_d, "IsShootByPlayer", -1);
    changeChild("投擲", &params);
}

float ReflectableBulletThrown::m35() {
    return *mReclectSpd_s;
}

}  // namespace uking::ai
