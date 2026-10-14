#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class LynelStandBody : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(LynelStandBody, ksys::act::ai::Behavior)
public:
    explicit LynelStandBody(const InitArg& arg);
    ~LynelStandBody() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const float* mStandRatioFB_s{};
    /* 0x30 */ const float* mStandRatioLR_s{};
    /* 0x38 */ void* mLynelBodyControlUnit_a{};
};
KSYS_CHECK_SIZE_NX150(LynelStandBody, 0x40);

}  // namespace uking::behavior
