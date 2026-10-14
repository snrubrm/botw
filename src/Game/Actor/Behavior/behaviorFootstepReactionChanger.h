#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class FootstepReactionChanger : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(FootstepReactionChanger, ksys::act::ai::Behavior)
public:
    explicit FootstepReactionChanger(const InitArg& arg);
    ~FootstepReactionChanger() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void loadParams() override;
    void m8() override;  // not decompiled yet (0x7100e363fc)
    void m9() override;  // not decompiled yet (0x7100e36420)

    /* 0x28 */ const int* mChangeDuration_s{};
    /* 0x30 */ sead::SafeString mReactionType_s{};
    /* 0x40 */ sead::SafeString mScaleType_s{};
    /* 0x50 */ s32 _50 = 0;
    /* 0x54 */ s32 _54 = 2;
};
KSYS_CHECK_SIZE_NX150(FootstepReactionChanger, 0x58);

}  // namespace uking::behavior
