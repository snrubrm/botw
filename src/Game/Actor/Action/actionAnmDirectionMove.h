#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmDirectionMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnmDirectionMove, ksys::act::ai::Action)
public:
    explicit AnmDirectionMove(const InitArg& arg);
    ~AnmDirectionMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mDirection_s{};
    // static_param at offset 0x28
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x30
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x38
    const bool* mIsChangeable_s{};
    // static_param at offset 0x40
    const bool* mUsereachableCheck_s{};
    // static_param at offset 0x48
    sead::SafeString mASName_s{};
    f32 _58 = 0.0f;
    sead::Vector3f _5c{0.0f, 0.0f, 1.0f};
    f32 _68 = 1.0f;
    u8 _6c[0x4];

    // 0x7100095aa0: moves a point in front of the actor (`_5c * _68 * scale` rotated by its matrix) and
    // returns the horizontal distance to the position the probe 0x710072fbd4 reports; `scale` itself if
    // the reachability check is off.
    f32 sub_7100095AA0(f32 scale);
    // 0x7100095bd0: hands the stored direction (rotated into the actor's frame) and the ratio to the
    // character controller.
    void sub_7100095BD0();
};
KSYS_CHECK_SIZE_NX150(AnmDirectionMove, 0x70);

}  // namespace uking::action
