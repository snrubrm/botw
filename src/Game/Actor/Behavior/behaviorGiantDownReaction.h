#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class GiantDownReaction : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(GiantDownReaction, ksys::act::ai::Behavior)
public:
    explicit GiantDownReaction(const InitArg& arg);
    ~GiantDownReaction() override;
    bool init_(sead::Heap* heap) override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void calc() override;

    /* 0x28 */ const int* mIntervalTime_s{};
    /* 0x30 */ sead::SafeString mDownCheckRagdollRbName_s{};
    /* 0x40 */ sead::SafeString mGroundCheckRagdollRbName_s[3]{};
    /* 0x70 */ bool _70 = false;
    /* 0x74 */ f32 _74 = 0.0f;
};
KSYS_CHECK_SIZE_NX150(GiantDownReaction, 0x78);

}  // namespace uking::behavior
