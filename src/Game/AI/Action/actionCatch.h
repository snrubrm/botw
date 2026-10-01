#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class Catch : public ActionEx {
    SEAD_RTTI_OVERRIDE(Catch, ActionEx)
public:
    explicit Catch(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const float* mRotSpd_s{};
    // dynamic_param at offset 0x30
    ksys::act::BaseProcLink* mTargetWeapon_d{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
    // unknown object (0x24 bytes; same type as TurnBase::_6c, methods 0x7100741034...)
    u8 _48[0x6c - 0x48];
    ksys::VFRValue _6c;
    ksys::VFRValue _78;
    bool _84 = false;
    bool _85 = false;
};

KSYS_CHECK_SIZE_NX150(Catch, 0x88);

}  // namespace uking::action
