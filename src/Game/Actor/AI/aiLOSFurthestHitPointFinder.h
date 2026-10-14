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
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_7100484D58(sead::Vector3f* out);

    // inline-only in the original; name is a guess (enter_ and calc_ (twice) repeat it): `_38` is a valid point that
    // is more than 0.01 away from the actor in x or z.
    bool isTargetAwayFromActor() const;
    // inline-only in the original; name is a guess (enter_ (twice) and calc_ (twice)): starts 行動A towards `_38`.
    void changeToActionA();

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
    u8 _68 = 0;  // number of enters without a hit point
    bool _69 = false;
};

}  // namespace uking::ai
