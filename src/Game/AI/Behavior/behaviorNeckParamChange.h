#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class NeckParamChange : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(NeckParamChange, ksys::act::ai::Behavior)
public:
    explicit NeckParamChange(const InitArg& arg);
    ~NeckParamChange() override;
    bool m6(sead::Heap* heap) override;
    void loadParams() override;
    void m7() override;  // not decompiled yet (0x710062cc2c)
    void m8() override;  // not decompiled yet (0x710062ca00)
    void m9() override;  // not decompiled yet (0x710062cd44)

    /* 0x28 */ const float* mULimit_s{};
    /* 0x30 */ const float* mDLimit_s{};
    /* 0x38 */ const float* mLLimit_s{};
    /* 0x40 */ const float* mRLimit_s{};
    /* 0x48 */ const float* mRotRatio_s{};
    /* 0x50 */ const float* mRetRotRatio_s{};
    /* 0x58 */ const float* mMinRotate_s{};
    /* 0x60 */ const float* mMaxRotate_s{};
    /* 0x68 */ const float* mOffsetLR_s{};
    /* 0x70 */ const float* mOffsetUD_s{};
    /* 0x78 */ u32 _78[9]{};
};
KSYS_CHECK_SIZE_NX150(NeckParamChange, 0xa0);

}  // namespace uking::behavior
