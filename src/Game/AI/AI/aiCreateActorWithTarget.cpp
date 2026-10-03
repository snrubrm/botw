#include "Game/AI/AI/aiCreateActorWithTarget.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

CreateActorWithTarget::CreateActorWithTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CreateActorWithTarget::~CreateActorWithTarget() = default;

bool CreateActorWithTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CreateActorWithTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _98 = ksys::Timer(30.0f, 30.0f);
    _a4 = ksys::Timer(*mCreateContinueTime_s, *mCreateContinueTime_s);
    _b0 = ksys::Timer(*mAfterWaitTime_s, *mAfterWaitTime_s);
    for (auto& handle : _c0)
        handle.deleteProc();
    _f0 = 0;
    const f32 num_pos = *mCreateBasePosNum_s + 1;
    const f32 interval = (*mCreateContinueTime_s + 2.0f) / num_pos;
    _f4 = interval;
    _f8 = ksys::Timer(interval, interval);
    mActor->getLodState()->mFlags10.setBit(6);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(m35(), "TargetPos", -1);
    changeChild("子ノード", &pack);
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
