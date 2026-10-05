#pragma once

#include "Game/AI/aiUnk_71024f15f8.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseEscapeRouteRailAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseEscapeRouteRailAI, ksys::act::ai::Ai)
public:
    explicit HorseEscapeRouteRailAI(const InitArg& arg);
    ~HorseEscapeRouteRailAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_7100E5BE9C(bool reset_ride_state);
    // static_param at offset 0x38
    const int* mCount_s{};
    // static_param at offset 0x40
    const float* mUpdatePosDistance_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    Unk_71024f15f8 _50;
    s32 _c0 = 0;
};
KSYS_CHECK_SIZE_NX150(HorseEscapeRouteRailAI, 0xc8);

}  // namespace uking::ai
