#pragma once

#include "Game/Actor/AI/aiGuardianCommonBeamAttack.h"
#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class RemainsWindBatteryAttack : public GuardianCommonBeamAttack {
    SEAD_RTTI_OVERRIDE(RemainsWindBatteryAttack, GuardianCommonBeamAttack)
public:
    explicit RemainsWindBatteryAttack(const InitArg& arg);
    ~RemainsWindBatteryAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    ksys::act::BaseProcLink _38[5];
    gsys::BoneAccessKeyEx _88;
    // dynamic_param at offset 0xc0
    sead::Vector3f* mTargetPos_d{};
};
KSYS_CHECK_SIZE_NX150(RemainsWindBatteryAttack, 0xc8);

}  // namespace uking::ai
