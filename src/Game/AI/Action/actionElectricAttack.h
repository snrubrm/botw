#pragma once

#include "Game/AI/Action/actionTimeredASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class ElectricAttack : public TimeredASPlay {
    SEAD_RTTI_OVERRIDE(ElectricAttack, TimeredASPlay)
public:
    explicit ElectricAttack(const InitArg& arg);
    ~ElectricAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100103684 (declared only): out of line in the original.
    bool sub_7100103684();
    // 0x71001034e0 (declared only): out of line in the original.
    void sub_71001034E0();
    // 0x7100103040 (declared only): out of line in the original.
    bool sub_7100103040(sead::Heap* heap);
    // 0x7100103830 (declared only): out of line in the original.
    void sub_7100103830();
    void calc_() override;

    // static_param at offset 0x60
    const float* mVoltage_s{};
    // static_param at offset 0x68
    const int* mMaxTimer_s{};
    // static_param at offset 0x70
    const int* mMaxKeepTimer_s{};
    // static_param at offset 0x78
    const int* mHitAfterTime_s{};
    // static_param at offset 0x80
    sead::SafeString mElectricActorName_s{};
    // static_param at offset 0x90
    sead::SafeString mElectricActorKey_s{};
    u32 _a0 = 0;
    ksys::Timer _a4{0.0f, 0.0f};
    ksys::Timer _b0{0.0f, 0.0f};
    bool _bc = false;
};

}  // namespace uking::action
