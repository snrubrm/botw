#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RailMoveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RailMoveBase, ksys::act::ai::Action)
public:
    explicit RailMoveBase(const InitArg& arg);
    ~RailMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();

    /* 0x1c */ sead::Vector3f _1c = sead::Vector3f::zero;
    // static_param at offset 0x28
    const float* mSpeed_s{};
    // dynamic_param at offset 0x30
    int* mASSlot_d{};
    // dynamic_param at offset 0x38
    int* mSequenceBank_d{};
    // dynamic_param at offset 0x40
    bool* mIsIgnoreSame_d{};
    // dynamic_param at offset 0x48
    sead::SafeString mASName_d{};
};

}  // namespace uking::action
