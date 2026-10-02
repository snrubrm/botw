#pragma once

#include "Game/AI/AI/aiBreathAttackEnemyBattle.h"
#include "Game/AI/aiGuardianAimBeamState.h"
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

class MiniBeamAttack : public BreathAttackEnemyBattle {
    SEAD_RTTI_OVERRIDE(MiniBeamAttack, BreathAttackEnemyBattle)
public:
    explicit MiniBeamAttack(const InitArg& arg);
    ~MiniBeamAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool isChangeable() const override;
    const sead::Vector3f* m35() override;
    void m37() override;
    void m41() override;

    virtual s32 m45();

protected:
    // static_param at offset 0xb0
    const float* mFluctuationRange_s{};
    // static_param at offset 0xb8
    const float* mFluctuationSpan_s{};
    // static_param at offset 0xc0
    const float* mTargetOffsetY_s{};
    // static_param at offset 0xc8
    sead::SafeString mNodeName_s{};
    // static_param at offset 0xd8
    const bool* mIsValidGuide_s{};
    // static_param at offset 0xe0
    const bool* mIsIgnoreSmallHit_s{};
    // static_param at offset 0xe8
    const bool* mIsChangeable_s{};
    // static_param at offset 0xf0
    sead::SafeString mAimEffectName_s{};
    GuardianAimBeamState _100;
    Unk_7102451ba0 _1f8;
    sead::Vector3f _220{0, 0, 0};
    Unk_71012419b4 _230{};
};
KSYS_CHECK_SIZE_NX150(MiniBeamAttack, 0x250);

}  // namespace uking::ai
