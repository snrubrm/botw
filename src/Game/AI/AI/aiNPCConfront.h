#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class NPCConfront : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCConfront, ksys::act::ai::Ai)
public:
    explicit NPCConfront(const InitArg& arg);
    ~NPCConfront() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71004c4aec: for the damage field-54 values 15 / 12 / 11 stores whether the attacker equals the second attacker link
    bool sub_71004C4AEC(bool* out);
    // static_param at offset 0x38
    const int* mCounterGuardCount_s{};
    // static_param at offset 0x40
    const float* mReleaseDistance_s{};
    // static_param at offset 0x48
    const float* mReleaseTime_s{};
    // static_param at offset 0x50
    const float* mCounterRate_s{};
    // static_param at offset 0x58
    const float* mDirectTurnAngle_s{};
    // dynamic_param at offset 0x60
    int* mTerrorLevel_d{};
    // dynamic_param at offset 0x68
    bool* mIsTimeOver_d{};
    // dynamic_param at offset 0x70
    bool* mIsSitting_d{};
    // dynamic_param at offset 0x78
    bool* mIsNeedUnEquipWeapon_d{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x88
    ksys::act::BaseProcLink* mTerrorEmitter_d{};
    bool _90 = false;  // GParamList Npc IsNotTurnDetect
    bool _91 = false;
    bool _92 = false;
    bool _93 = false;
    bool _94 = false;
    bool _95 = false;
    bool _96 = false;
    sead::Vector3f _98;
    ksys::Timer _a4;
    ksys::Timer _b0;
    u32 _bc = 0;
};
KSYS_CHECK_SIZE_NX150(NPCConfront, 0xc0);

}  // namespace uking::ai
