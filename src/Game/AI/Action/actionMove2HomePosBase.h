#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>

namespace uking::action {

class Move2HomePosBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Move2HomePosBase, ksys::act::ai::Action)
public:
    explicit Move2HomePosBase(const InitArg& arg);
    ~Move2HomePosBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsReturn_s{};
    // dynamic_param at offset 0x28
    float* mDynMoveDis_d{};
    // dynamic_param at offset 0x30
    float* mDynMoveSpeed_d{};
    sead::Vector3f _38 = sead::Vector3f::zero;
    sead::Vector3f _44 = sead::Vector3f::zero;
};

KSYS_CHECK_SIZE_NX150(Move2HomePosBase, 0x50);

}  // namespace uking::action
