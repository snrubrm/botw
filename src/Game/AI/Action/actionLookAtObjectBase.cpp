#include "Game/AI/Action/actionLookAtObjectBase.h"

namespace uking::action {

LookAtObjectBase::LookAtObjectBase(const InitArg& arg) : PlayerAction(arg) {}

LookAtObjectBase::~LookAtObjectBase() = default;

bool LookAtObjectBase::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void LookAtObjectBase::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void LookAtObjectBase::leave_() {}

void LookAtObjectBase::loadParams_() {
    getDynamicParam(&mObjectId_d, "ObjectId");
    getDynamicParam(&mFaceId_d, "FaceId");
    getDynamicParam(&mTurnDirection_d, "TurnDirection");
    getDynamicParam(&mIsValid_d, "IsValid");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mPosOffset_d, "PosOffset");
    getDynamicParam(&mTurnPosition_d, "TurnPosition");
}

void LookAtObjectBase::calc_() {}

void LookAtObjectBase::m33() {
    _30 = *mObjectId_d;
    _34 = *mFaceId_d;
    _38.set(sead::Vector3f::zero);
    _68.set(sead::Vector3f::zero);
    _44 = false;
    _45 = *mIsValid_d;
    _48 = mActorName_d;
    _58 = mUniqueName_d;
}

}  // namespace uking::action
