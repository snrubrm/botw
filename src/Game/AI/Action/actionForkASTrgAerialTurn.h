#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>

namespace uking::action {

class ForkASTrgAerialTurn : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASTrgAerialTurn, ksys::act::ai::Action)
public:
    explicit ForkASTrgAerialTurn(const InitArg& arg);
    ~ForkASTrgAerialTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPosStayRatio_s{};
    // static_param at offset 0x28
    const float* mRotStayRatio_s{};
    // static_param at offset 0x30
    const float* mAngSpd_s{};
    // static_param at offset 0x38
    const bool* mIsOnASEventChangeable_s{};
    // static_param at offset 0x40
    const bool* mIsUpdateRotSpd_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    sead::Vector3f _50 = sead::Vector3f::zero;
    u32 _5c = 0;
};

KSYS_CHECK_SIZE_NX150(ForkASTrgAerialTurn, 0x60);

}  // namespace uking::action
