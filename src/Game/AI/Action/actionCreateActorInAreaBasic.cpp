#include "Game/AI/Action/actionCreateActorInAreaBasic.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::action {

CreateActorInAreaBasic::CreateActorInAreaBasic(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CreateActorInAreaBasic::~CreateActorInAreaBasic() = default;

bool CreateActorInAreaBasic::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CreateActorInAreaBasic::enter_(ksys::act::ai::InlineParamPack* params) {
    _a8 = ksys::Timer(*mCreateNewActorIntervalFirst_s, *mCreateNewActorIntervalFirst_s);
    _b4 = ksys::Timer(*mCreateContinueTime_s, *mCreateContinueTime_s);
    _c0 = ksys::Timer(*mAfterWaitTime_s, *mAfterWaitTime_s);
    auto* actor = mActor;
    _78.deleteProc();
    _88.deleteProc();
    _98.deleteProc();
    _dc = 0.0f;
    const f32 count = static_cast<f32>(*mCreateBasePosNum_s + 1);
    const f32 interval = (*mCreateContinueTime_s + 2.0f) / count;
    _d8 = interval;
    _cc = ksys::Timer(interval, interval);
    if (auto* lod = actor->getLodState())
        lod->mFlags10.set(0x40);
}

void CreateActorInAreaBasic::leave_() {
    auto* actor = mActor;
    _78.deleteProc();
    _88.deleteProc();
    _98.deleteProc();
    if (auto* lod = actor->getLodState())
        lod->mFlags10.reset(0x40);
}

void CreateActorInAreaBasic::loadParams_() {
    getStaticParam(&mCreateBasePosNum_s, "CreateBasePosNum");
    getStaticParam(&mCreateNewActorIntervalFirst_s, "CreateNewActorIntervalFirst");
    getStaticParam(&mCreateNewActorInterval_s, "CreateNewActorInterval");
    getStaticParam(&mCreateContinueTime_s, "CreateContinueTime");
    getStaticParam(&mAfterWaitTime_s, "AfterWaitTime");
    getStaticParam(&mIsAllowCreateNoSafeArea_s, "IsAllowCreateNoSafeArea");
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getStaticParam(&mBaseOffset_s, "BaseOffset");
    getStaticParam(&mCreateRandArea_s, "CreateRandArea");
    getStaticParam(&mProhibitedCreateArea_s, "ProhibitedCreateArea");
}

void CreateActorInAreaBasic::m33(sead::Vector3f* pos) {
    pos->set(getPlayerPosition());
}

bool CreateActorInAreaBasic::m34() {
    if (_b4.value <= sead::Mathf::epsilon()) {
        _c0.update();
        if (_c0.value <= sead::Mathf::epsilon())
            return true;
    }
    return false;
}

void CreateActorInAreaBasic::calc_() {
    _a8.update();
    _b4.update();
    _cc.update();
    if (m34())
        setFinished();
    else
        m32();
}

}  // namespace uking::action
