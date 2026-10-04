#pragma once

#include "Game/AI/Action/actionForkDropWeapon.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkOnEnterDropWeaponWithSpeed : public ForkDropWeapon {
    SEAD_RTTI_OVERRIDE(ForkOnEnterDropWeaponWithSpeed, ForkDropWeapon)
public:
    explicit ForkOnEnterDropWeaponWithSpeed(const InitArg& arg);
    ~ForkOnEnterDropWeaponWithSpeed() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710014ce28 (declared only): out of line in the original.
    void sub_710014CE28();
    void calc_() override;
};

}  // namespace uking::action
