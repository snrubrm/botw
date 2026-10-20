#pragma once

#include "Game/Actor/AI/aiEnemyDefaultReaction.h"
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
    bool m38(act::DamageManagerBase* damage_mgr) override { return false; }

    // 0x710057fb10: when the boss wears or draws its flame: _73 = true, flame part state, x_1 and flag 0x80000
    void sub_710057FB10();
    // 0x710057fc40: enters the flame reaction child when the boss wears or draws its flame, otherwise switches
    // to the effective damage child; builds the six reaction parameters and runs EnemyDefaultReaction::m40.
    void sub_710057FC40();
    // 0x7100581050: starts the flame reaction: bit 9 of _14c8._30, bit 19 of _1558 at half life, disables the
    // flame cloth entry and tells the boss through SiteBoss::sub_71002CFD04.
    void sub_7100581050();

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
