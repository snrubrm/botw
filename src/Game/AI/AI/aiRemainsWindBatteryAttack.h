#pragma once

#include "Game/AI/AI/aiGuardianBeamAttackBase.h"
#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class RemainsWindBatteryAttack : public GuardianBeamAttackBase {
    SEAD_RTTI_OVERRIDE(RemainsWindBatteryAttack, GuardianBeamAttackBase)
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
