#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class AnimalNeckRotate : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AnimalNeckRotate, ksys::act::ai::Behavior)
public:
    explicit AnimalNeckRotate(const InitArg& arg);
    ~AnimalNeckRotate() override;
    bool m6(sead::Heap* heap) override;
    void loadParams() override;
    void m7() override;  // not decompiled yet (0x7100617618)
    void m8() override;  // not decompiled yet (0x7100617490)
    void m9() override;  // not decompiled yet (0x7100617a04)

    /* 0x28 */ const float* mLimitAngleLR_s{};
    /* 0x30 */ const float* mRotRate_s{};
    /* 0x38 */ const float* mResetRotRate_s{};
    /* 0x40 */ const bool* mIsUseParentRotOffset_s{};
    /* 0x48 */ gsys::BoneAccessKeyEx _48;
};
KSYS_CHECK_SIZE_NX150(AnimalNeckRotate, 0x80);

}  // namespace uking::behavior
