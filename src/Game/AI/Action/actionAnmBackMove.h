#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmBackMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnmBackMove, ksys::act::ai::Action)
public:
    explicit AnmBackMove(const InitArg& arg);
    ~AnmBackMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x28
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    u64 _40 = 0;
    s32 _48 = 0;
    f32 _4c = -1.0f;

};
KSYS_CHECK_SIZE_NX150(AnmBackMove, 0x50);

}  // namespace uking::action
