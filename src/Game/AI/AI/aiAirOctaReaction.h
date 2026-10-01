#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AirOctaReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(AirOctaReaction, EnemyDefaultReaction)
public:
    explicit AirOctaReaction(const InitArg& arg);
    ~AirOctaReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m34(dmg::DamageManagerBase* damage_mgr, int damage_type) override;
    void m35(dmg::DamageManagerBase* damage_mgr, int damage_type, bool x,
             ksys::act::ai::InlineParamPack* params) override;
    void m42(ksys::act::ai::InlineParamPack* params) override;

protected:
    // aitree_variable at offset 0x68
    void* mAirOctaDataMgr_a{};
};

}  // namespace uking::ai
