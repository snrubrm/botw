#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class GanonBattleOnFloorRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonBattleOnFloorRoot, ksys::act::ai::Ai)
public:
    explicit GanonBattleOnFloorRoot(const InitArg& arg);
    ~GanonBattleOnFloorRoot() override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_71003E1EE0(bool no_wait);

    // static_param at offset 0x38
    const float* mFarAttackDist_s{};
    // dynamic_param at offset 0x40
    bool* mIsNoWait_d{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _50{};
    bool _5c{};
};

}  // namespace uking::ai
