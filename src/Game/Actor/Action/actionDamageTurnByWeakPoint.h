#pragma once

#include <math/seadMatrix.h>

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DamageTurnByWeakPoint : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DamageTurnByWeakPoint, ksys::act::ai::Action)
public:
    explicit DamageTurnByWeakPoint(const InitArg& arg);
    ~DamageTurnByWeakPoint() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71000e6400 (declared only): out of line in the original.
    void sub_71000E6400();
    void calc_() override;

    // static_param at offset 0x20
    const float* mTurnSpeed_s{};
    // static_param at offset 0x28
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x30
    const float* mAngReduceRatio_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
    sead::Vector3f _48 = sead::Vector3f::zero;
    sead::Matrix33f _54;

};
KSYS_CHECK_SIZE_NX150(DamageTurnByWeakPoint, 0x78);

}  // namespace uking::action
