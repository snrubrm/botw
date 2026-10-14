#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class LynelBodyFitToGroundNormal : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(LynelBodyFitToGroundNormal, ksys::act::ai::Behavior)
public:
    explicit LynelBodyFitToGroundNormal(const InitArg& arg);
    ~LynelBodyFitToGroundNormal() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const float* mCorrectAngleMax_s{};
    /* 0x30 */ void* mLynelBodyControlUnit_a{};
};
KSYS_CHECK_SIZE_NX150(LynelBodyFitToGroundNormal, 0x38);

}  // namespace uking::behavior
