#pragma once

#include "KingSystem/System/Timer.h"
#include "Game/AI/Action/actionBlownOff.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ElectricBlownOff : public BlownOff {
    SEAD_RTTI_OVERRIDE(ElectricBlownOff, BlownOff)
public:
    explicit ElectricBlownOff(const InitArg& arg);
    ~ElectricBlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710010451c (declared only): out of line in the original.
    void sub_710010451C();
    // 0x7100103e00 (declared only): out of line in the original.
    bool sub_7100103E00(sead::Heap* heap);
    void calc_() override;

    // static_param at offset 0x160
    const float* mVoltage_s{};
    // static_param at offset 0x168
    const int* mMaxTimer_s{};
    // static_param at offset 0x170
    const int* mMaxKeepTimer_s{};
    // static_param at offset 0x178
    sead::SafeString mElectricActorName_s{};
    // static_param at offset 0x188
    sead::SafeString mElectricActorKey_s{};
    u32 _198 = 0;
    ksys::Timer _19c{0, 0};
    u8 _1a8 = 0xff;
};

}  // namespace uking::action
