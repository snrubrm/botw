#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RideHorseAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RideHorseAI, ksys::act::ai::Ai)
public:
    explicit RideHorseAI(const InitArg& arg);
    ~RideHorseAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic2_param at offset 0x38
    bool* mHasToPlayRidingOnAS_d{};
    u32 _40 = 0;
};
KSYS_CHECK_SIZE_NX150(RideHorseAI, 0x48);

}  // namespace uking::ai
