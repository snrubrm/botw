#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(GanonReaction, EnemyDefaultReaction)
public:
    explicit GanonReaction(const InitArg& arg);
    ~GanonReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool m34(dmg::DamageManagerBase* damage_mgr, int damage_type) override;
    bool m36(int damage_type) override;
    void m40(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;

    bool _63{};
};

}  // namespace uking::ai
