#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class AwarenessScale : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AwarenessScale, ksys::act::ai::Behavior)
public:
    explicit AwarenessScale(const InitArg& arg);
    ~AwarenessScale() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const float* mSight_s;
    /* 0x30 */ const float* mHearing_s;
    /* 0x38 */ const float* mTerror_s;
    /* 0x40 */ const float* mWorry_s;
};
KSYS_CHECK_SIZE_NX150(AwarenessScale, 0x48);

}  // namespace uking::behavior
