#pragma once

#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Behavior/behaviorGuardFrontBarrierBase.h"

namespace uking::behavior {

class GuardFrontBarrier : public GuardFrontBarrierBase {
    SEAD_RTTI_OVERRIDE(GuardFrontBarrier, GuardFrontBarrierBase)
public:
    explicit GuardFrontBarrier(const InitArg& arg);
    ~GuardFrontBarrier() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    virtual void m15(sead::Matrix34f* out);

    /* 0x78 */ sead::SafeString mTgtName_s{};
};
KSYS_CHECK_SIZE_NX150(GuardFrontBarrier, 0x88);

}  // namespace uking::behavior
