#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class BgmCtrlBehavior : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(BgmCtrlBehavior, ksys::act::ai::Behavior)
public:
    explicit BgmCtrlBehavior(const InitArg& arg);
    ~BgmCtrlBehavior() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const float* mFadeTime_s{};
    /* 0x30 */ sead::SafeString mCtrlType_s{};
    /* 0x40 */ sead::SafeString mBgmName_s{};
};
KSYS_CHECK_SIZE_NX150(BgmCtrlBehavior, 0x50);

}  // namespace uking::behavior
