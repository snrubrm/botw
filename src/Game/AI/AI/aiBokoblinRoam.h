#pragma once

#include <math/seadVector.h>

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class BokoblinRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BokoblinRoam, ksys::act::ai::Ai)
public:
    explicit BokoblinRoam(const InitArg& arg);
    // Inline in the original; Timer members preserve the standalone base destructor.
    ~BokoblinRoam() override = default;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

    // 0x7100333e68 / 0x7100333f7c / 0x7100333fec (placeholder names)
    bool sub_7100333E68();
    void changeToSearch();
    void sub_7100333FEC();
    // 0x71003349e0 (placeholder name)
    void changeToIdle();
    // 0x71003344ac (placeholder name)
    void changeToRotate();
    // 0x710033433c (placeholder name): ray cast ahead of the actor (TurnCheckDist, TurnCheckHeight)
    bool sub_710033433C();

protected:
    // static_param at offset 0x38
    const int* mFreeIntervalMin_s{};
    // static_param at offset 0x40
    const int* mFreeIntervalMax_s{};
    // static_param at offset 0x48
    const int* mFreePer_s{};
    // static_param at offset 0x50
    const int* mMoveIntervalMin_s{};
    // static_param at offset 0x58
    const int* mMoveIntervalMax_s{};
    // static_param at offset 0x60
    const int* mNoMoveTime_s{};
    // static_param at offset 0x68
    const int* mNoSpAttackMoveTime_s{};
    // static_param at offset 0x70
    const int* mSpAttackServiceTime_s{};
    // static_param at offset 0x78
    const float* mTerritory_s{};
    // static_param at offset 0x80
    const float* mTargetDistMin_s{};
    // static_param at offset 0x88
    const float* mTargetDistMax_s{};
    // static_param at offset 0x90
    const float* mSpAttackServiceDist_s{};
    // static_param at offset 0x98
    const float* mSpAttackServiceAngle_s{};
    // dynamic_param at offset 0xa0
    sead::Vector3f* mCentralPos_d{};
    // static_param at offset 0xa8
    const float* mTurnCheckDist_s{};
    // static_param at offset 0xb0
    const float* mTurnCheckHeight_s{};
    f32 _b8{};
    s32 _bc{};
    s32 _c0{};
    ksys::Timer _c4;
    ksys::Timer _d0;
    bool _dc{};
    bool _dd{};
};

}  // namespace uking::ai
