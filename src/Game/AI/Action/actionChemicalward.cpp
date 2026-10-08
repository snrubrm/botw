#include "Game/AI/Action/actionChemicalward.h"
#include <gsys/gsysModel.h>
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
    playAS("Burnward", false, 0, 0, -1.0f);
    _13c = sead::Matrix34f::ident;
    auto* model = mActor->getModel();
    if (*mNodeName_s.getStringTop() == sead::SafeString::cNullChar)
        return;
    gsys::BoneAccessKey key = model->searchBone(mNodeName_s);
    if (!key.isValid())
        return;
    _138 = key;
    _90.setName(mNodeName_s);
    _90._68 = _13c;
    mActor->boneHandleStuff(&_90, false);
    _16c = 0;
    _17c = 0;
    _170 = static_cast<f32>(*mStableTime_s);
    _174 = static_cast<f32>(*mKeepTime_s);
    _178 = static_cast<f32>(*mTiredTime_s);
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
