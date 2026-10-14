#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

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
    ksys::Timer _6c;
    ksys::Timer _78;
    ksys::Timer _84;
    u8 _90 = 0;
    sead::Vector3f _94;
    sead::Matrix33f _a0;
    u8 _c4[0x4];

private:
    // 0x710026b5d8 (placeholder name): spawns the bound actor `idx` of the SiteBoss at the pose `front`
    // / `pos`, facing the target.
    void sub_710026B5D8(int idx, const sead::Vector3f* front, const sead::Vector3f* pos, f32 value);
};
KSYS_CHECK_SIZE_NX150(SiteBossSwordMove, 0xc8);

}  // namespace uking::action
