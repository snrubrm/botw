#pragma once
#include "KingSystem/XLink/xlinkActorUtil.h"

#include "Game/AI/Action/actionRemainsWaterBulletAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemainsWaterExplodeBulletMove : public RemainsWaterBulletAction {
    SEAD_RTTI_OVERRIDE(RemainsWaterExplodeBulletMove, RemainsWaterBulletAction)
public:
    explicit RemainsWaterExplodeBulletMove(const InitArg& arg);
    ~RemainsWaterExplodeBulletMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100233fd0 (declared only): out of line in the original.
    void sub_7100233FD0();
    void calc_() override;
    void m32() override;

    // static_param at offset 0x80
    const float* mMaxSpeed_s{};
    // static_param at offset 0x88
    const float* mCloseRadius_s{};
    // static_param at offset 0x90
    const float* mChaseAngleMulRate_s{};
    // static_param at offset 0x98
    const float* mFarRadius_s{};
    // static_param at offset 0xa0
    const float* mChaseRotSpdRate_s{};
    // static_param at offset 0xa8
    const float* mChaseSpdRate_s{};
    // map_unit_param at offset 0xb0
    const float* mRemainsWaterBulletAngle_m{};
    // map_unit_param at offset 0xb8
    const sead::Vector3f* mRemainsWaterBulletOffset_m{};
    bool _c0 = false;
    Unk_71012419b4 _c8;
    f32 _e8 = 1.0f;
    f32 _ec = 1.0f;
};

}  // namespace uking::action
