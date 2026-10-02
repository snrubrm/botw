#pragma once

#include "Game/AI/AI/aiUnarmedEnemySearchWeapon.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class UnarmedWeaponEquipableEnemyAct : public UnarmedEnemySearchWeapon {
    SEAD_RTTI_OVERRIDE(UnarmedWeaponEquipableEnemyAct, UnarmedEnemySearchWeapon)
public:
    explicit UnarmedWeaponEquipableEnemyAct(const InitArg& arg);
    ~UnarmedWeaponEquipableEnemyAct() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool _6e8 = false;
};

}  // namespace uking::ai
