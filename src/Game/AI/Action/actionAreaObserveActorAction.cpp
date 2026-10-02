#include "Game/AI/Action/actionAreaObserveActorAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

AreaObserveActorAction::AreaObserveActorAction(const InitArg& arg) : AreaActorObserve(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
AreaObserveActorAction::~AreaObserveActorAction() {
    ;
}

void AreaObserveActorAction::m9() {
    if (mActor)
        mActor->setFlag(ksys::act::Actor::ActorFlag::_1c, *mForceCalcInEvent_m);
}

void AreaObserveActorAction::m32() {
    getMapUnitParam(&mActorName_m, "ActorName");
    getMapUnitParam(&mTargetUniqueName_m, "TargetUniqueName");
    getMapUnitParam(&mForceCalcInEvent_m, "ForceCalcInEvent");
    getMapUnitParam(&mIsMagneGrabbed_m, "IsMagneGrabbed");
    getMapUnitParam(&mIsStopFromStopTimer_m, "IsStopFromStopTimer");
    if (mActor)
        mActor->setFlag(ksys::act::Actor::ActorFlag::_1c, *mForceCalcInEvent_m);
}

bool AreaObserveActorAction::m37(const ksys::act::ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;

    if (accessor.getName() != mActorName_m)
        return false;

    switch (*mIsMagneGrabbed_m) {
    case 1:
        if (!accessor.sub_7100D13BB8())
            return false;
        break;
    case 2:
        if (accessor.sub_7100D13BB8())
            return false;
        break;
    }

    switch (*mIsStopFromStopTimer_m) {
    case 1:
        if (!accessor.sub_7100D10FB8())
            return false;
        break;
    case 2:
        if (accessor.sub_7100D10FB8())
            return false;
        break;
    }

    if (mTargetUniqueName_m.isEmpty())
        return true;

    const char* unique_name = accessor.getUniqueName();
    if (!unique_name)
        return false;
    return mTargetUniqueName_m == unique_name;
}

}  // namespace uking::action
