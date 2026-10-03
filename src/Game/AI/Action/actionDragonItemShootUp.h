#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DragonItemShootUp : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DragonItemShootUp, ksys::act::ai::Action)
public:
    explicit DragonItemShootUp(const InitArg& arg);
    ~DragonItemShootUp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mFlyAwaySpeed_s{};
    // static_param at offset 0x28
    const float* mContactSpeedDownXZ_s{};
    // static_param at offset 0x30
    const float* mContactSpeedDownY_s{};
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    sead::Vector3f _40 = sead::Vector3f::zero;
    s32 _4c = 0;
    u16 _50 = 0;
    u8 _52[0xe];

};
KSYS_CHECK_SIZE_NX150(DragonItemShootUp, 0x60);

}  // namespace uking::action
