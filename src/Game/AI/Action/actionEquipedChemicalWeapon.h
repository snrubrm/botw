#pragma once

#include "Game/AI/Action/actionEquipedAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EquipedChemicalWeapon : public EquipedAction {
    SEAD_RTTI_OVERRIDE(EquipedChemicalWeapon, EquipedAction)
public:
    explicit EquipedChemicalWeapon(const InitArg& arg);
    ~EquipedChemicalWeapon() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;

    // 0x710010e614: a player's weapon (not m214) with an unused charge record and a normal request type.
    bool sub_710010E614();
};

}  // namespace uking::action
