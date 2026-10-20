#include "KingSystem/ActorSystem/actEventTag.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/System/MCMgr.h"

namespace ksys::act {

BaseProc* EventTag::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) EventTag(arg);
}

EventTag::EventTag(const CreateArg& arg) : Actor(arg) {
    for (auto& handler : mJobHandlers)
        handler = nullptr;

    if (mName == "SignalFlowchart") {
        getJobHandler(JobType::Calc3) = &mJob0;
        mIsSignalFlowchart = true;
    } else if (mName == "EventTag") {
        getJobHandler(JobType::Calc1) = &mJob1;
        getJobHandler(JobType::Calc3Alt) = &mJob0;
    }
}

void EventTag::calcAi() {
    if (deleteIfPlacementStuff())
        return;
    if (mRootAi)
        mRootAi->calc();
    _8e0 = false;
}

void EventTag::initMaybe() {
    _8e2 = 0;
    _8e0 = false;
}

// NON_MATCHING: ours reuses the map object flag load of the Calc1 / Calc3Alt case for the final check (the
// original loads it again).
bool EventTag::shouldSkipJobPush_(JobType type) {
    switch (type) {
    case JobType::Calc3Alt:
        if (_1a0)
            return true;
        if (mMapObject && mMapObject->getFlags0().isOn(map::Object::Flag0::_20000))
            return true;
        break;
    case JobType::Calc1:
        if (_1a0)
            return false;
        if (!mMapObject || !mMapObject->getFlags0().isOn(map::Object::Flag0::_20000))
            return true;
        break;
    default:
        if (_1a0)
            return false;
        break;
    }
    if (mMapObject && mMapObject->getFlags0().isOn(map::Object::Flag0::_20000))
        return false;
    return !_8e0;
}

// NON_MATCHING: the type test at the end compares 6 before 1. The map object flag load there has no use; it
// is in the original (the flags are atomic).
void EventTag::onJobPush2_(JobType type) {
    if (mIsSignalFlowchart) {
        if (auto* mgr = MCMgr::instance()) {
            const s32 value = mgr->get1be4();
            if (_8e2 == value || (value == 0 && checkBasicSig()))
                _8e0 = true;
        }
    } else if (_8e2 >= 0) {
        _8e0 = true;
    }
    _8e2 = -1;

    if (shouldSkipJobPush(type) && !mIsSignalFlowchart) {
        if ((type == JobType::Calc1 || type == JobType::Calc3Alt) && !_1a0 && mMapObject)
            mMapObject->getFlags0().isOn(map::Object::Flag0::_20000);
    }
}

// NON_MATCHING: the original sign-extends the MCMgr value into the stored register (sxtb).
void EventTag::m107() {
    s8 value = 0;
    if (mIsSignalFlowchart) {
        if (auto* mgr = MCMgr::instance()) {
            value = s8(mgr->get1be4());
            if (value > 0 && hasJobType_(JobType::Calc3))
                BaseProcMgr::instance()->mPushActorJobType3InsteadOf6 = true;
        }
    }
    _8e2 = value;
}

EventTag::~EventTag() = default;

}  // namespace ksys::act
