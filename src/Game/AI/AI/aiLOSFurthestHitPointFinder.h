#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LOSFurthestHitPointFinder : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LOSFurthestHitPointFinder, ksys::act::ai::Ai)
public:
    explicit LOSFurthestHitPointFinder(const InitArg& arg);
    ~LOSFurthestHitPointFinder() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    sead::Vector3f _38{0, 0, 0};
    // static_param at offset 0x48
    const int* mMaxNumCheck_s{};
    // static_param at offset 0x50
    const float* mCheckDistance_s{};
    // static_param at offset 0x58
    const bool* mOnlyCheckBehind_s{};
    // static_param at offset 0x60
    const bool* mUseActionB_s{};
    bool _68 = false;
    bool _69 = false;
};

}  // namespace uking::ai
