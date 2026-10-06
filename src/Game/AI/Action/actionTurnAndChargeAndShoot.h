#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/System/VFRValue.h"
#include "Game/AI/Action/actionChargeAndShoot.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TurnAndChargeAndShoot : public ChargeAndShoot {
    SEAD_RTTI_OVERRIDE(TurnAndChargeAndShoot, ChargeAndShoot)
public:
    explicit TurnAndChargeAndShoot(const InitArg& arg);
    ~TurnAndChargeAndShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m34() override;

    // 0x710029d8f8 (placeholder name): the turn direction towards the target (+1 / -1; 0 when straight ahead).
    s32 sub_710029D8F8();
    // 0x710029da28 (placeholder name): turns the actor towards the target while a turn is going on (_e8), or applies
    // the stop rotation speed otherwise.
    void sub_710029DA28();

    // static_param at offset 0xb0
    const float* mRotSpeed_s{};
    sead::Matrix33f _b8;
    ksys::VFRValue _dc;
    int _e8 = 0;
};

}  // namespace uking::action
