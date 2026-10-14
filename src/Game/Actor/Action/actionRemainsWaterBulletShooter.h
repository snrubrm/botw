#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::action {

class RemainsWaterBulletShooter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainsWaterBulletShooter, ksys::act::ai::Action)
public:
    explicit RemainsWaterBulletShooter(const InitArg& arg);
    ~RemainsWaterBulletShooter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71002311f0 (declared only): out of line in the original.
    void sub_71002311F0();
    void calc_() override;

    // static_param at offset 0x20
    const int* mBulletType_s{};
    // static_param at offset 0x28
    const int* mReloadCounter_s{};
    // static_param at offset 0x30
    const float* mOffsetAngle_s{};
    // static_param at offset 0x38
    const bool* mUseRandRot_s{};
    // static_param at offset 0x40
    const sead::Vector3f* mIgniteRotate_s{};
    // static_param at offset 0x48
    const sead::Vector3f* mBaseShootParam_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mOffsetYParam_s{};
    // aitree_variable at offset 0x58
    void* mRemainsWaterBattleInfo_a{};
    ksys::act::Unk_7100d3bce4 _60{mActor};
    u8 _78[0x30];
    s32 _a8 = 0;
    bool _ac = true;
    u8 _ad[0x3];
};
KSYS_CHECK_SIZE_NX150(RemainsWaterBulletShooter, 0xb0);

}  // namespace uking::action
