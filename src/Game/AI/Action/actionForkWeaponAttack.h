#pragma once

#include "Game/AI/Action/actionForkWeaponAttackBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkWeaponAttack : public ForkWeaponAttackBase {
    SEAD_RTTI_OVERRIDE(ForkWeaponAttack, ForkWeaponAttackBase)
public:
    explicit ForkWeaponAttack(const InitArg& arg);
    ~ForkWeaponAttack() override;

    void loadParams_() override;

protected:
    int m36() override;

    // static_param at offset 0x70
    const int* mWeaponIdx_s{};
};

}  // namespace uking::action
