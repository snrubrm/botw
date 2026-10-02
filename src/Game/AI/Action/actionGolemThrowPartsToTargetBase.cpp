#include "Game/AI/Action/actionGolemThrowPartsToTargetBase.h"
#include "Game/Damage/dmgDamageCallback.h"

namespace uking::action {

GolemThrowPartsToTargetBase::GolemThrowPartsToTargetBase(const InitArg& arg) : ActionWithAS(arg) {}

GolemThrowPartsToTargetBase::~GolemThrowPartsToTargetBase() = default;

bool GolemThrowPartsToTargetBase::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void GolemThrowPartsToTargetBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    setDamageCallbackTiming(mActor, 4, &_f0);
    mFlags.reset(Flag::Changeable);
}

void GolemThrowPartsToTargetBase::leave_() {
    ActionWithAS::leave_();
}

void GolemThrowPartsToTargetBase::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mTgtBodyName_s, "TgtBodyName");
    getStaticParam(&mChmObjectName_s, "ChmObjectName");
    _60.sub_71005E1BE8(this, 0);
    _a0.sub_71005E1BE8(this, 1);
    _e0 = false;
    _e1 = false;
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void GolemThrowPartsToTargetBase::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
