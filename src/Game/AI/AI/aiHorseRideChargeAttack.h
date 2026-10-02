#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class HorseRideChargeAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseRideChargeAttack, ksys::act::ai::Ai)
public:
    explicit HorseRideChargeAttack(const InitArg& arg);
    ~HorseRideChargeAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    void sub_710043EFAC();

protected:
    // static_param at offset 0x38
    const int* mUpperBodyASSlot_s{};
    // static_param at offset 0x40
    const int* mLowerBodyASSlot_s{};
    // static_param at offset 0x48
    const int* mWeaponIdx_s{};
    // static_param at offset 0x50
    const float* mAttackableAngle_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    Unk_71023fbad8 _60;
    bool _98{};
    ksys::Timer _9c;
};

}  // namespace uking::ai
