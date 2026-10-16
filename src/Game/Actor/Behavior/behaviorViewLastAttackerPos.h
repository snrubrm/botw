#pragma once

#include "Game/Actor/Behavior/behaviorNeckControl.h"

namespace uking::behavior {

class ViewLastAttackerPos : public NeckControl {
    SEAD_RTTI_OVERRIDE(ViewLastAttackerPos, NeckControl)
public:
    explicit ViewLastAttackerPos(const InitArg& arg);
    ~ViewLastAttackerPos() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void m15(sead::Vector3f* out) override;

};
KSYS_CHECK_SIZE_NX150(ViewLastAttackerPos, 0x38);

}  // namespace uking::behavior
