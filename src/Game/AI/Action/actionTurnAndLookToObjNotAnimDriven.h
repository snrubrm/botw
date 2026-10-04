#pragma once

#include "Game/AI/Action/actionLookAtObjectBase.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class CharacterController;
}

namespace uking::action {

class TurnAndLookToObjNotAnimDriven : public LookAtObjectBase {
    SEAD_RTTI_OVERRIDE(TurnAndLookToObjNotAnimDriven, LookAtObjectBase)
public:
    explicit TurnAndLookToObjNotAnimDriven(const InitArg& arg);
    ~TurnAndLookToObjNotAnimDriven() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m40();
    // 0x71002a0b24 (not decompiled yet): called by calc_ with the character controller.
    virtual void m41(ksys::phys::CharacterController* controller);

    // dynamic_param at offset 0xc8
    float* mRotSpdMax_d{};
    // dynamic_param at offset 0xd0
    float* mRotSpdMin_d{};
    // dynamic_param at offset 0xd8
    float* mRotInitSpd_d{};
    // dynamic_param at offset 0xe0
    float* mRotAccel_d{};
    // dynamic_param at offset 0xe8
    float* mRotRate_d{};
    bool _f0 = false;
    bool _f1 = false;
    ksys::VFRValue _f4;
    u8 _100[0x128 - 0x100];
};
KSYS_CHECK_SIZE_NX150(TurnAndLookToObjNotAnimDriven, 0x128);

}  // namespace uking::action
