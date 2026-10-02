#pragma once

#include "Game/AI/Behavior/behaviorNeckControl.h"

namespace uking::behavior {

class ViewLastAttackerPos : public NeckControl {
    SEAD_RTTI_OVERRIDE(ViewLastAttackerPos, NeckControl)
public:
    explicit ViewLastAttackerPos(const InitArg& arg);
    ~ViewLastAttackerPos() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m15(sead::Vector3f* out) override;  // TODO 0x7100646c20

};
KSYS_CHECK_SIZE_NX150(ViewLastAttackerPos, 0x38);

}  // namespace uking::behavior
