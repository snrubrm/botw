#pragma once

#include "Game/AI/Action/actionBattleCloseMoveAction.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {
class BattleCloseExplosivesAvoidRun;
}

// vtable 0x710236b490 (BattleCloseExplosivesAvoidRun damage callback; no RTTI of its own, its D2 slot
// is DamageCallback's). Zeroes the damage when the attacker is at least DamageIgnoreDist away.
// Placeholder name.
class Unk_710236b490 : public uking::dmg::DamageCallback {
public:
    explicit Unk_710236b490(uking::action::BattleCloseExplosivesAvoidRun* owner) : mOwner(owner) {}
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    uking::action::BattleCloseExplosivesAvoidRun* mOwner;
};

namespace uking::action {

class BattleCloseExplosivesAvoidRun : public BattleCloseMoveAction {
    SEAD_RTTI_OVERRIDE(BattleCloseExplosivesAvoidRun, BattleCloseMoveAction)
    friend class ::Unk_710236b490;

public:
    explicit BattleCloseExplosivesAvoidRun(const InitArg& arg);
    ~BattleCloseExplosivesAvoidRun() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void m32(sead::Vector3f* target_pos) override;

    // static_param at offset 0xa8
    const float* mDamageIgnoreDist_s{};
    Unk_710236b490 _b0{this};
};
KSYS_CHECK_SIZE_NX150(BattleCloseExplosivesAvoidRun, 0xe0);

}  // namespace uking::action
