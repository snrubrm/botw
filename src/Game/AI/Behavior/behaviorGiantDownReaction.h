#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class GiantDownReaction : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(GiantDownReaction, ksys::act::ai::Behavior)
public:
    explicit GiantDownReaction(const InitArg& arg);
    ~GiantDownReaction() override;
    bool m6(sead::Heap* heap) override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m7() override;  // not decompiled yet (0x7100624a1c)

    /* 0x28 */ const int* mIntervalTime_s{};
    /* 0x30 */ sead::SafeString mDownCheckRagdollRbName_s{};
    /* 0x40 */ sead::SafeString _40{};
    /* 0x50 */ sead::SafeString _50{};
    /* 0x60 */ sead::SafeString _60{};
    /* 0x70 */ bool _70 = false;
    /* 0x74 */ f32 _74 = 0.0f;
};
KSYS_CHECK_SIZE_NX150(GiantDownReaction, 0x78);

}  // namespace uking::behavior
