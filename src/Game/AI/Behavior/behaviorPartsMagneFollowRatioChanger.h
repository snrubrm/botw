#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

// vtable 0x7102437f38 (functions in this behavior's translation unit): sends message 0x80000b1 with a ratio.
class Unk_7102437f38 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    f32 _18 = 1.0f;
};

class PartsMagneFollowRatioChanger : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(PartsMagneFollowRatioChanger, ksys::act::ai::Behavior)
public:
    explicit PartsMagneFollowRatioChanger(const InitArg& arg);
    ~PartsMagneFollowRatioChanger() override;
    bool m6(sead::Heap* heap) override;
    void m8() override;
    void loadParams() override;
    void m7() override;  // not decompiled yet (0x7100632734)
    void m9() override;  // not decompiled yet (0x7100632824)

    /* 0x28 */ const float* mRatio_s{};
    /* 0x30 */ sead::SafeString mPartsName_s{};
    /* 0x40 */ Unk_7102437f38 _40{mActor, 0x80000b1};
};
KSYS_CHECK_SIZE_NX150(PartsMagneFollowRatioChanger, 0x60);

}  // namespace uking::behavior
