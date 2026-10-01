#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include <xlink2/xlink2Handle.h>
#include "KingSystem/ActorSystem/actAiAi.h"

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
    // effect object (CSV eft::Effect::x_0 / fadeXLink are called on &_70)
    xlink2::Handle _70;
    xlink2::Handle _80;
    bool _90 = false;
};

}  // namespace uking::ai
