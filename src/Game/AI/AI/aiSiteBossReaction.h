#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(SiteBossReaction, EnemyDefaultReaction)
public:
    explicit SiteBossReaction(const InitArg& arg);
    ~SiteBossReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool m36(int damage_type) override;
    bool m38(dmg::DamageManagerBase* damage_mgr) override { return false; }

protected:
    // static_param at offset 0x68
    const bool* mIsChangeEffectiveDamage_s{};
    bool _70 = false;
    bool _71 = false;
    bool _72 = false;
    bool _73 = false;
    s32 _74 = 0;
    // not initialised by the ctor and unused by the AI functions
    u8 _78[0xa0 - 0x78];
};
KSYS_CHECK_SIZE_NX150(SiteBossReaction, 0xa0);

}  // namespace uking::ai
