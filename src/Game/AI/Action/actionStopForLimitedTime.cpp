#include "Game/AI/Action/actionStopForLimitedTime.h"
#include "math/seadMathCalcCommon.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

StopForLimitedTime::StopForLimitedTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StopForLimitedTime::~StopForLimitedTime() = default;

bool StopForLimitedTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StopForLimitedTime::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = 0.0f;
    if (auto* body = mActor->getMainBody())
        body->changePositionAndRotation(mActor->getMtx(), sead::Mathf::epsilon());
    if (!mASKeyName_s.isEmpty())
        playAS(mASKeyName_s.cstr(), false, 0, 0, -1.0f);
}

void StopForLimitedTime::leave_() {
    ksys::act::ai::Action::leave_();
}

void StopForLimitedTime::loadParams_() {
    getStaticParam(&mKeepActRotation_s, "KeepActRotation");
    getStaticParam(&mEnableStaticCompoundRotate_s, "EnableStaticCompoundRotate");
    getStaticParam(&mIsSetEndByTime_s, "IsSetEndByTime");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mDynStopTime_d, "DynStopTime");
    getDynamicParam(&mDynStopPos_d, "DynStopPos");
}

void StopForLimitedTime::calc_() {
    ksys::act::ai::Action::calc_();
}

bool StopForLimitedTime::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!ksys::act::ai::Action::reenter_(other, true))
        return false;
    auto* action = sead::DynamicCast<StopForLimitedTime>(other);
    if (!action)
        return false;
    _58 = action->_58;
    return true;
}

}  // namespace uking::action
