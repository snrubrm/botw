#pragma once

#include "Game/AI/AI/aiMiniBeamAttack.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class GuardianMiniBeamAttack : public MiniBeamAttack {
    SEAD_RTTI_OVERRIDE(GuardianMiniBeamAttack, MiniBeamAttack)
public:
    explicit GuardianMiniBeamAttack(const InitArg& arg);
    ~GuardianMiniBeamAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    // 0x710041705c: not defined yet (calls several unnamed helpers of this TU).
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool isChangeable() const override;

protected:
    // static_param at offset 0x250
    sead::SafeString mHeadNodeName_s{};
    // static_param at offset 0x260
    const int* mAttackInterval_s{};
    // static_param at offset 0x268
    const int* mEndShaderASFrame_s{};
    // static_param at offset 0x270
    sead::SafeString mLoopShaderASName_s{};
    // static_param at offset 0x280
    sead::SafeString mEndShaderASName_s{};
    // static_param at offset 0x290
    sead::SafeString mPreLaunchEffectName_s{};
    // static_param at offset 0x2a0
    const bool* mIsChangeable_s{};
    // static_param at offset 0x2a8
    const bool* mIsFinalBattle_s{};
    // static_param at offset 0x2b0
    const float* mInDirAngle_s{};
    sead::Vector3f _2b8{0, 0, 0};
    ksys::Timer _2c4{0, 0};
    f32 _2d0{};
};
KSYS_CHECK_SIZE_NX150(GuardianMiniBeamAttack, 0x2d8);

}  // namespace uking::ai
