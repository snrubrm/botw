#include "Game/AI/Action/actionStopForLimitedTime.h"
#include "math/seadMathCalcCommon.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/System/VFR.h"

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

// NON_MATCHING: store order of the identity + translation matrix (the original writes the diagonal first and the
// translation afterwards) and cbnz vs tbnz on the chase result.
void StopForLimitedTime::calc_() {
    auto* actor = mActor;
    if (ksys::VFR::chase(&_58, *mDynStopTime_d)) {
        mFlags.set(Flag::Changeable);
        if (*mIsSetEndByTime_s)
            setFinished();
    }
    sead::Matrix34f rot_mtx;
    if (*mKeepActRotation_s)
        rot_mtx = actor->getMtx();
    else
        actor->getHomeMtx(&rot_mtx);
    sead::Matrix34f mtx;
    mtx.makeT(*mDynStopPos_d);
    if (auto* body = actor->getMainBody()) {
        if (auto* mgr = ksys::phys::System::instance()->getStaticCompoundMgr()) {
            if (*mEnableStaticCompoundRotate_s)
                mtx = mgr->getTransformedMatrix(actor->getFieldBodyGroup(), mtx);
        }
        sead::Vector3f translation;
        mtx.getTranslation(translation);
        rot_mtx.setTranslation(translation);
        body->changePositionAndRotation(rot_mtx, sead::Mathf::epsilon());
    }
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
