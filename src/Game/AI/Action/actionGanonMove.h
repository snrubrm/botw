#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GanonMove, ksys::act::ai::Action)
public:
    explicit GanonMove(const InitArg& arg);
    ~GanonMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMoveSpeed_s{};
    // static_param at offset 0x28
    const float* mMoveAccel_s{};
    // static_param at offset 0x30
    const float* mAvoidMoveSpeed_s{};
    // static_param at offset 0x38
    const float* mAvoidMoveAccel_s{};
    // static_param at offset 0x40
    const bool* mIsUpEqualGravity_s{};
    // static_param at offset 0x48
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x58
    bool* mIsChangeable_d{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mDstPos_d{};
    f32 _70 = 0.0f;
    u8 _74[0x48];
    s32 _bc[2]{};
    u8 _c4[0x4];
    gsys::BoneAccessKeyEx _c8;
};
KSYS_CHECK_SIZE_NX150(GanonMove, 0x100);

}  // namespace uking::action
