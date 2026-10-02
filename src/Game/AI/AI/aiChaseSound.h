#pragma once

#include <math/seadVector.h>

#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class RayCastForRequest;
}

namespace uking::ai {

class ChaseSound : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ChaseSound, ksys::act::ai::Ai)
public:
    explicit ChaseSound(const InitArg& arg);
    ~ChaseSound() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mNearDist_s{};
    // static_param at offset 0x40
    const float* mTurnDir_s{};
    // static_param at offset 0x48
    const int* mTargetUpdateIntervalMin_s{};
    // static_param at offset 0x50
    const int* mTargetUpdateIntervalMax_s{};
    // static_param at offset 0x58
    const bool* mUseViewPointSimpleOffset_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    sead::Vector3f _68{0, 0, 0};
    u32 _74{};
    ksys::phys::RayCastForRequest* _78{};
    sead::Vector3f _80;
    bool _8c = false;
};

}  // namespace uking::ai
