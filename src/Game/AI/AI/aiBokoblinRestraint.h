#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class BokoblinRestraint : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BokoblinRestraint, ksys::act::ai::Ai)
public:
    explicit BokoblinRestraint(const InitArg& arg);
    ~BokoblinRestraint() override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100332bf0 (placeholder name): spawns a "Rock_Weapon" (random scale 0.8 - 1.2) at the actor unless it
    // has a connected calc child / an actor already, then changeChild("威嚇") with the target.
    void sub_7100332BF0();
    // 0x7100333040: true when the spawned actor is ready (then 0x71003332b4); respawns after a failure.
    bool sub_7100333040();
    // 0x71003332b4 (declared only).
    void sub_71003332B4();
    void spawnRock();
    // 0x71003331a0 (declared only): whether the target is out of reach (restarts the lost timer while it is in reach).
    bool sub_71003331A0();

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x40
    const float* mBaseDist_s{};
    // static_param at offset 0x48
    const float* mLostVMin_s{};
    // static_param at offset 0x50
    const float* mLostVMax_s{};
    // static_param at offset 0x58
    const int* mLostTimer_s{};
    // static_param at offset 0x60
    const float* mLostRange_s{};
    ksys::act::BaseProcHandle _68;
    ksys::Timer _78{0, 0};
    bool _84 = true;
};

}  // namespace uking::ai
