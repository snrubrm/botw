#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

// Placeholder name (vtable 0x7102414f60; inherits DamageCallback's RTTI; `call` 0x7100528494,
// D0 0x71005285a8). PriestBossNormalReaction::_80.
class Unk_7102414f60 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};
KSYS_CHECK_SIZE_NX150(Unk_7102414f60, 0x28);

class PriestBossNormalReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(PriestBossNormalReaction, EnemyDefaultReaction)
public:
    explicit PriestBossNormalReaction(const InitArg& arg);
    ~PriestBossNormalReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool m34(dmg::DamageManagerBase* damage_mgr, int damage_type) override;
    void m35(dmg::DamageManagerBase* damage_mgr, int damage_type, bool x,
             ksys::act::ai::InlineParamPack* params) override;
    bool m45() override;

protected:
    // static_param at offset 0x68
    const bool* mIsUseQuickRecover_s{};
    // aitree_variable at offset 0x70
    bool* mPriestBossUrbosasFuryEShock_a{};
    // aitree_variable at offset 0x78
    void* mPriestBossMetaAIUnit_a{};
    Unk_7102414f60 _80;
    Unk_71012419b4 _a8;
    bool _c8 = false;
    bool _c9 = false;
};
KSYS_CHECK_SIZE_NX150(PriestBossNormalReaction, 0xd0);

}  // namespace uking::ai
