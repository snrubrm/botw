#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossLswordFirstCreateFBall : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossLswordFirstCreateFBall, ksys::act::ai::Action)
public:
    explicit SiteBossLswordFirstCreateFBall(const InitArg& arg);
    ~SiteBossLswordFirstCreateFBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    struct Params {
        // static_param at offset 0x20
        const int* mAtMinDamage_s{};
        // static_param at offset 0x28
        const int* mAttackPower_s{};
        // static_param at offset 0x30
        const int* mCreateNum_s{};
        // static_param at offset 0x38
        const int* mAddAttackPower_s{};
        // static_param at offset 0x40
        const float* mFireBallScale_s{};
        // static_param at offset 0x48
        sead::SafeString mThrowActorName_s{};
        // static_param at offset 0x58
        sead::SafeString mASName_s{};
        // static_param at offset 0x68
        const sead::Vector3f* mBindPosOffset_s{};
    };
    Params mParams;
    bool _70 = false;
    u8 _71[0x3];
    f32 _74 = 0.0f;
    f32 _78 = 0.0f;
    f32 _7c = 0.0f;
};
KSYS_CHECK_SIZE_NX150(SiteBossLswordFirstCreateFBall, 0x80);

}  // namespace uking::action
