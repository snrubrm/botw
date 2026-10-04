#pragma once

#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimTimingAttackMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnimTimingAttackMove, ksys::act::ai::Action)
public:
    explicit AnimTimingAttackMove(const InitArg& arg);
    ~AnimTimingAttackMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mJumpHeight_s{};
    // static_param at offset 0x28
    const float* mMaxSpeed_s{};
    // static_param at offset 0x30
    const bool* mIsRound_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
    // static_param at offset 0x48
    sead::SafeString mRigidBodyName_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    ksys::VFRValue _60;
    s32 _6c = 0;
    u8 _70 = 0;
    u8 _71 = 1;
    bool _72 = true;
    u8 _73[0x5];
};
KSYS_CHECK_SIZE_NX150(AnimTimingAttackMove, 0x78);

}  // namespace uking::action
