#pragma once

#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmUpDownMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnmUpDownMove, ksys::act::ai::Action)
public:
    explicit AnmUpDownMove(const InitArg& arg);
    ~AnmUpDownMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x28
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x30
    const float* mAccRatio_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
    u64 _48 = 0;
    f32 _50 = 0.0f;
    ksys::act::CCAccessor _54;
    u8 _5c[0x4];
};
KSYS_CHECK_SIZE_NX150(AnmUpDownMove, 0x60);

}  // namespace uking::action
