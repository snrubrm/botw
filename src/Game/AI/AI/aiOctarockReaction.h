#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OctarockReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(OctarockReaction, EnemyDefaultReaction)
public:
    explicit OctarockReaction(const InitArg& arg);
    ~OctarockReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m34(dmg::DamageManagerBase* damage_mgr, int damage_type) override;
    void m35(dmg::DamageManagerBase* damage_mgr, int damage_type, bool x,
             ksys::act::ai::InlineParamPack* params) override;
    void m39(ksys::act::ai::InlineParamPack* params) override;
    void m42(ksys::act::ai::InlineParamPack* params) override;

protected:
    void sub_71004ED6D4();

    // static_param at offset 0x68
    const bool* mIsWigBreackByGust_s{};
    // aitree_variable at offset 0x70
    void* mOctarockFormChangeUnit_a{};
};
KSYS_CHECK_SIZE_NX150(OctarockReaction, 0x78);

}  // namespace uking::ai
