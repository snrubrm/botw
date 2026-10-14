#pragma once

#include <math/seadVector.h>
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
    f32 _40 = 0;
    sead::Vector3f _44{0.0f, 0.0f, -1.0f};

    // 0x71000942b8: turns the stored direction into the actor's frame and hands it, with the ratio,
    // to the character controller.
    void sub_71000942B8();
};
KSYS_CHECK_SIZE_NX150(AnmBackMove, 0x50);

}  // namespace uking::action
