#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Behavior/behaviorOnChangeXLinkCreate.h"

namespace uking::behavior {

class OnChangeXLinkCreateAtTarget : public OnChangeXLinkCreate {
    SEAD_RTTI_OVERRIDE(OnChangeXLinkCreateAtTarget, OnChangeXLinkCreate)
public:
    explicit OnChangeXLinkCreateAtTarget(const InitArg& arg);
    ~OnChangeXLinkCreateAtTarget() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m14() override;
    // 0x7100630570
    void sub_7100630570();

    /* 0x40 */ sead::SafeString mTargetUniqueName_s{};
    /* 0x50 */ sead::Vector3f _50{sead::Vector3f::zero};
};
KSYS_CHECK_SIZE_NX150(OnChangeXLinkCreateAtTarget, 0x60);

}  // namespace uking::behavior
