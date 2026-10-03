#include "Game/AI/AI/aiCreateActorWithTarget.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

CreateActorWithTarget::CreateActorWithTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CreateActorWithTarget::~CreateActorWithTarget() = default;

bool CreateActorWithTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CreateActorWithTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CreateActorWithTarget::calc_() {
    _98.update();
    _a4.update();
    _f8.update();
    if (m36()) {
        setFinished();
        return;
    }
    m34();
    getCurrentChild()->setDynamicParam(m35(), "TargetPos");
}

void CreateActorWithTarget::leave_() {
    for (auto& handle : _c0)
        handle.deleteProc();
    mActor->getLodState()->mFlags10.resetBit(6);
}

void CreateActorWithTarget::loadParams_() {
    getStaticParam(&mCreateNewActorInterval_s, "CreateNewActorInterval");
    getStaticParam(&mCreateBasePosNum_s, "CreateBasePosNum");
    getStaticParam(&mCreateContinueTime_s, "CreateContinueTime");
    getStaticParam(&mAfterWaitTime_s, "AfterWaitTime");
    getStaticParam(&mIsAllowCreateNoSafeArea_s, "IsAllowCreateNoSafeArea");
    getStaticParam(&mIsRotateTargetDir_s, "IsRotateTargetDir");
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getStaticParam(&mBaseOffset_s, "BaseOffset");
    getStaticParam(&mCreateRandArea_s, "CreateRandArea");
    getStaticParam(&mProhibitedCreateArea_s, "ProhibitedCreateArea");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

sead::Vector3f CreateActorWithTarget::m35() {
    return *mTargetPos_d;
}

bool CreateActorWithTarget::m36() {
    if (_a4.value <= sead::Mathf::epsilon()) {
        _b0.update();
        if (_b0.value <= sead::Mathf::epsilon())
            return true;
    }
    return false;
}

void CreateActorWithTarget::m37() {}

}  // namespace uking::ai
