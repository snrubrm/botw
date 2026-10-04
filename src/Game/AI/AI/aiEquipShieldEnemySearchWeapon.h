#pragma once

#include "Game/AI/AI/aiUnarmedEnemySearchWeapon.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EquipShieldEnemySearchWeapon : public UnarmedEnemySearchWeapon {
    SEAD_RTTI_OVERRIDE(EquipShieldEnemySearchWeapon, UnarmedEnemySearchWeapon)
public:
    explicit EquipShieldEnemySearchWeapon(const InitArg& arg);
    ~EquipShieldEnemySearchWeapon() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    void m44() override;
    void m45() override;
    bool m46(ksys::act::BaseProcLink& target) override;

protected:
    bool _6e8 = false;
};

KSYS_CHECK_SIZE_NX150(EquipShieldEnemySearchWeapon, 0x6f0);

}  // namespace uking::ai
