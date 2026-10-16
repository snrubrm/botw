#include "Game/Actor/Action/actionCreateActorInAreaBasic.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "Game/gameResetter.h"
#include <math/seadMathCalcCommon.h>
#include <math/seadBoundBox.h>
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actLodState.h"
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
    for (auto& handle : _78)
        handle.deleteProc();
    _dc = 0;
    const f32 count = static_cast<f32>(*mCreateBasePosNum_s + 1);
    const f32 interval = (*mCreateContinueTime_s + 2.0f) / count;
    _d8 = interval;
    _cc = ksys::Timer(interval, interval);
    if (auto* lod = actor->getLodState())
        lod->mFlags10.set(0x40);
}

void CreateActorInAreaBasic::leave_() {
    auto* actor = mActor;
    for (auto& handle : _78)
        handle.deleteProc();
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

void CreateActorInAreaBasic::m32() {
    if (_a8.value <= sead::Mathf::epsilon()) {
        if (Resetter::instance()->finishedReset()) {
            if (_cc.value <= sead::Mathf::epsilon() && _dc < *mCreateBasePosNum_s) {
                ++_dc;
                _cc = ksys::Timer(_d8, _d8);
            } else {
                const sead::Vector3f& area = *mCreateRandArea_s;
                for (s32 i = 0; i < 7; ++i) {
                    const f32 x = sead::GlobalRandom::instance()->getF32Range(-area.x, area.x);
                    const f32 y = sead::GlobalRandom::instance()->getF32Range(-area.y, area.y);
                    const f32 z = sead::GlobalRandom::instance()->getF32Range(-area.z, area.z);
                    const sead::BoundBox3f prohibited_area(-*mProhibitedCreateArea_s,
                                                           *mProhibitedCreateArea_s);
                    if (prohibited_area.isInside({x, y, z}) &&
                        !(i == 6 && *mIsAllowCreateNoSafeArea_s))
                        continue;

                    sead::Vector3f pos;
                    m33(&pos);
                    pos.setAdd(sead::Vector3f(x, y, z) + *mBaseOffset_s, pos);
                    for (auto& handle : _78) {
                        if (handle.isAllocatedOrFailed())
                            continue;
                        ksys::act::InstParamPack params;
                        params->addPosition(pos);
                        auto* creator = ksys::act::ActorCreator::instance();
                        mCreateActorName_s.cstr();
                        creator->requestCreateActor(
                            mCreateActorName_s.getStringTop(),
                            ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &handle, &params,
                            nullptr, 1);
                        break;
                    }
                    break;
                }
            }
        }
        _a8 = ksys::Timer(*mCreateNewActorInterval_s, *mCreateNewActorInterval_s);
    }

    for (auto& handle : _78) {
        if (handle.isProcReady())
            handle.releaseAndWakeProc();
        else if (handle.hasProcCreationFailed())
            handle.deleteProcIfFailed();
    }
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
