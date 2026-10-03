#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class FadeLeaf : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(FadeLeaf, ksys::act::ai::Behavior)
public:
    explicit FadeLeaf(const InitArg& arg);
    ~FadeLeaf() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const float* mAlphaLower_s{};
    /* 0x30 */ const float* mAlphaSpeed_s{};
    /* 0x38 */ s32 _38[6];  // material indices (searchMaterial result >> 16)
    /* 0x50 */ f32 _50 = 1.0f;
};
KSYS_CHECK_SIZE_NX150(FadeLeaf, 0x58);

}  // namespace uking::behavior
