#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

class PriestBossGiantReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(PriestBossGiantReaction, EnemyDefaultReaction)
public:
    explicit PriestBossGiantReaction(const InitArg& arg);
    ~PriestBossGiantReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m34(dmg::DamageManagerBase* damage_mgr, int damage_type) override;
    void m35(dmg::DamageManagerBase* damage_mgr, int damage_type, bool x,
             ksys::act::ai::InlineParamPack* params) override;

protected:
    // aitree_variable at offset 0x68
    bool* mPriestBossUrbosasFuryEShock_a{};
    Unk_71012419b4 _70;
    bool _90 = false;
};

}  // namespace uking::ai
