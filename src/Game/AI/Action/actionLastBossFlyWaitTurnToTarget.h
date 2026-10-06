#pragma once

#include "KingSystem/System/VFRValue.h"
#include "Game/AI/Action/actionLastBossFlyWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossFlyWaitTurnToTarget : public LastBossFlyWait {
    SEAD_RTTI_OVERRIDE(LastBossFlyWaitTurnToTarget, LastBossFlyWait)
public:
    explicit LastBossFlyWaitTurnToTarget(const InitArg& arg);
    ~LastBossFlyWaitTurnToTarget() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71001d12d0 (declared only): the turning version of the flight target matrix.
    void m32(sead::Matrix34f* mtx) override;

    // static_param at offset 0xa0
    const float* mTurnStartDiffAng_s{};
    // static_param at offset 0xa8
    const float* mTurnRate_s{};
    // static_param at offset 0xb0
    sead::SafeString mTurnASName_s{};
    // dynamic_param at offset 0xc0
    sead::Vector3f* mTargetPos_d{};
    u8 _c8[0x24];
    ksys::VFRValue _ec;
    bool _f8 = false;
    u8 _f9[0x7];
};
KSYS_CHECK_SIZE_NX150(LastBossFlyWaitTurnToTarget, 0x100);

}  // namespace uking::action
