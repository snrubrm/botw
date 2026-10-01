#pragma once

#include <math/seadMatrix.h>
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
    sead::Matrix33f _48;
    ksys::VFRValue _6c;
    ksys::VFRValue _78;
    bool _84 = false;
    bool _85 = false;
};

KSYS_CHECK_SIZE_NX150(Catch, 0x88);

}  // namespace uking::action
