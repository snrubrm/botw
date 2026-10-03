#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossShadowClonesReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(PriestBossShadowClonesReaction, EnemyDefaultReaction)
public:
    explicit PriestBossShadowClonesReaction(const InitArg& arg);
    ~PriestBossShadowClonesReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m34(dmg::DamageManagerBase* damage_mgr, int damage_type) override;

protected:
    void sub_710052D98C();

    // aitree_variable at offset 0x68
    Unk_7102450fa8** mPriestBossMetaAIUnit_a{};
    bool _70{};
};

}  // namespace uking::ai
