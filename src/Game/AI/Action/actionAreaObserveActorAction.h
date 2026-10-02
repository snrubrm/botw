#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionAreaActorObserve.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaObserveActorAction : public AreaActorObserve {
    SEAD_RTTI_OVERRIDE(AreaObserveActorAction, AreaActorObserve)
public:
    explicit AreaObserveActorAction(const InitArg& arg);
    ~AreaObserveActorAction() override;

    void m9() override;

protected:
    void m32() override;
    bool m37(const ksys::act::ActorConstDataAccess& accessor) override;

    // map_unit_param (loaded by m32)
    sead::SafeString mActorName_m;
    // map_unit_param (loaded by m32)
    sead::SafeString mTargetUniqueName_m;
    // map_unit_param (loaded by m32)
    const bool* mForceCalcInEvent_m{};
    // map_unit_param (loaded by m32)
    const int* mIsMagneGrabbed_m{};
    // map_unit_param (loaded by m32)
    const int* mIsStopFromStopTimer_m{};
};
KSYS_CHECK_SIZE_NX150(AreaObserveActorAction, 0x98);

}  // namespace uking::action
