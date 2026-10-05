#pragma once

#include "Game/AI/Action/actionEquipedOptionalWeaponAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EquipedQuiver : public EquipedOptionalWeaponAction {
    SEAD_RTTI_OVERRIDE(EquipedQuiver, EquipedOptionalWeaponAction)
public:
    explicit EquipedQuiver(const InitArg& arg);
    ~EquipedQuiver() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    // Declaration only; the original also returns whether an arrow count was found.
    bool sub_710010FD20(s32* count);

protected:
    void calc_() override;
};

}  // namespace uking::action
