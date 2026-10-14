#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class CutGrass : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(CutGrass, ksys::act::ai::Behavior)
public:
    explicit CutGrass(const InitArg& arg);
    ~CutGrass() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const float* mCutRange_s{};
    /* 0x30 */ const float* mIntensity_s{};
    /* 0x38 */ const bool* mIsCallEffect_s{};
};
KSYS_CHECK_SIZE_NX150(CutGrass, 0x40);

}  // namespace uking::behavior
