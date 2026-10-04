#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "Game/AI/aiUnk_710073E688.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class SiteBossLswordTornadoAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossLswordTornadoAttack, ksys::act::ai::Action)
public:
    explicit SiteBossLswordTornadoAttack(const InitArg& arg);
    ~SiteBossLswordTornadoAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mEndTime_s{};
    // static_param at offset 0x28
    const float* mVacuumAcc_s{};
    // static_param at offset 0x30
    const float* mVacuumMaxSpeed_s{};
    // static_param at offset 0x38
    const float* mVacuumAngle_s{};
    // static_param at offset 0x40
    const float* mVacuumBaseWeight_s{};
    /* 0x48 */ bool _48 = false;
    /* 0x4c */ ksys::Timer _4c;
    /* 0x58 */ Unk_710073e688 _58;
};
KSYS_CHECK_SIZE_NX150(SiteBossLswordTornadoAttack, 0x88);

}  // namespace uking::action
