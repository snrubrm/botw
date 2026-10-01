#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::action {

class AnmDrivenHoverBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnmDrivenHoverBase, ksys::act::ai::Action)
public:
    explicit AnmDrivenHoverBase(const InitArg& arg);
    ~AnmDrivenHoverBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMoveYLimit_s{};
    // static_param at offset 0x28
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x40
    float* mBaseHeight_d{};
    ksys::act::CCAccessor mCCAccessor;
};

KSYS_CHECK_SIZE_NX150(AnmDrivenHoverBase, 0x50);

}  // namespace uking::action
