#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class LynelBodyFitToGroundNormal : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(LynelBodyFitToGroundNormal, ksys::act::ai::Behavior)
public:
    explicit LynelBodyFitToGroundNormal(const InitArg& arg);
    ~LynelBodyFitToGroundNormal() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const float* mCorrectAngleMax_s{};
    /* 0x30 */ void* mLynelBodyControlUnit_a{};
};
KSYS_CHECK_SIZE_NX150(LynelBodyFitToGroundNormal, 0x38);

}  // namespace uking::behavior
