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
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710054cfb0 (placeholder name): changes to 照準準備 (aim preparation) or 照準 (aim) with the target position;
    // on aim with the player as target, sends 0x800000e to the actors of the map object's links
    void sub_710054CFB0(bool prepare);
    // 0x710054d19c (declared only; 464 bytes): aims the free beam at the target; false when none is free
    bool sub_710054D19C();

    ksys::act::BaseProcLink _38[5];
    gsys::BoneAccessKeyEx _88;
    // dynamic_param at offset 0xc0
    sead::Vector3f* mTargetPos_d{};
};
KSYS_CHECK_SIZE_NX150(RemainsWindBatteryAttack, 0xc8);

}  // namespace uking::ai
