#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class LowCeilingController : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(LowCeilingController, ksys::act::ai::Behavior)
public:
    explicit LowCeilingController(const InitArg& arg);
    ~LowCeilingController() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    bool m6(sead::Heap* heap) override;  // not decompiled yet (0x710062b0a4)
    void m7() override;  // not decompiled yet (0x710062b134)

    /* 0x28 */ const float* mChangeFrame_s{};
    /* 0x30 */ const float* mReverseFrame_s{};
    /* 0x38 */ sead::SafeString mShapeName_s{};
    /* 0x48 */ u32 _48 = 0;
    /* 0x4c */ s32 _4c = -1;
    /* 0x50 */ u32 _50 = 0;
};
KSYS_CHECK_SIZE_NX150(LowCeilingController, 0x58);

}  // namespace uking::behavior
