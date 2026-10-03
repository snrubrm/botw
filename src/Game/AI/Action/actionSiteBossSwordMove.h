#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSwordMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossSwordMove, ksys::act::ai::Action)
public:
    explicit SiteBossSwordMove(const InitArg& arg);
    ~SiteBossSwordMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAfterImage0AppearFrame_s{};
    // static_param at offset 0x28
    const float* mAfterImage1AppearFrame_s{};
    // static_param at offset 0x30
    const float* mAppearFrame_s{};
    // dynamic_param at offset 0x38
    float* mCurrentFrame_d{};
    // dynamic_param at offset 0x40
    bool* mIsCloseMove_d{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mMoveDstPos_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mAfterImage0Pos_d{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mAfterImage1Pos_d{};
    s32 _68 = 0;
    f32 _6c = 0.0f;
    s32 _70 = 0;
    u8 _74[0x4]{};
    s32 _78 = 0;
    u8 _7c[0x4]{};
    s32 _80 = 0;
    s32 _84 = 0;
    u8 _88[0x4]{};
    s32 _8c = 0;
    bool _90 = false;
    u8 _91[0x37];
};
KSYS_CHECK_SIZE_NX150(SiteBossSwordMove, 0xc8);

}  // namespace uking::action
