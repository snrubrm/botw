#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpPlayerToReferenceAnchor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpPlayerToReferenceAnchor, ksys::act::ai::Action)
public:
    explicit WarpPlayerToReferenceAnchor(const InitArg& arg);
    ~WarpPlayerToReferenceAnchor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    sead::Vector3f _1c = sead::Vector3f::zero;
};
KSYS_CHECK_SIZE_NX150(WarpPlayerToReferenceAnchor, 0x28);

}  // namespace uking::action
