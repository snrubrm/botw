#include "Game/AI/Action/actionChemicalward.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace uking::action {

Chemicalward::Chemicalward(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

Chemicalward::~Chemicalward() = default;

bool Chemicalward::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void Chemicalward::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void Chemicalward::leave_() {
    ActionWithPosAngReduce::leave_();
    _90._68 = sead::Matrix34f::ident;
    mActor->sub_71011DA868(&_90);
}

void Chemicalward::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mNodeAxisIdx_s, "NodeAxisIdx");
    getStaticParam(&mStableTime_s, "StableTime");
    getStaticParam(&mKeepTime_s, "KeepTime");
    getStaticParam(&mTiredTime_s, "TiredTime");
    getStaticParam(&mTiredRadius_s, "TiredRadius");
    getStaticParam(&mTiredAngle_s, "TiredAngle");
    getStaticParam(&mVoltage_s, "Voltage");
    getStaticParam(&mNodeName_s, "NodeName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void Chemicalward::calc_() {
    ActionWithPosAngReduce::calc_();
}

bool Chemicalward::isChangeable() const {
    return false;
}

}  // namespace uking::action
