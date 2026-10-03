#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRideMoveTo : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseRideMoveTo, ksys::act::ai::Ai)
public:
    explicit HorseRideMoveTo(const InitArg& arg);
    ~HorseRideMoveTo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    // static_param at offset 0x38
    const int* mUpperBodyASSlot_s{};
    // static_param at offset 0x40
    const int* mLowerBodyASSlot_s{};
    // static_param at offset 0x48
    const int* mWeaponIdx_s{};
    // static_param at offset 0x50
    const float* mFinRadius_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    Unk_71023fc720 _60;
    Unk_71023fc750 _98;
};

}  // namespace uking::ai
