#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SwarmEscapeDie : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SwarmEscapeDie, ksys::act::ai::Ai)
public:
    explicit SwarmEscapeDie(const InitArg& arg);
    ~SwarmEscapeDie() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_71005B1464();
    void sub_71005B15F8();
    void sub_71005B19F8();

protected:
    // static_param at offset 0x38
    const int* mTime_s{};
    // static_param at offset 0x40
    const float* mRiseHeight_s{};
    // static_param at offset 0x48
    const float* mRiseDist_s{};
    // static_param at offset 0x50
    const float* mEndDist_s{};
    ksys::Timer _58;
    sead::Vector3f _64;
};
KSYS_CHECK_SIZE_NX150(SwarmEscapeDie, 0x70);

}  // namespace uking::ai
