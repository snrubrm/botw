#pragma once

#include "Game/AI/Action/actionForkEmitChmField.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkEmitChmFieldFromWeapon : public ForkEmitChmField {
    SEAD_RTTI_OVERRIDE(ForkEmitChmFieldFromWeapon, ForkEmitChmField)
public:
    explicit ForkEmitChmFieldFromWeapon(const InitArg& arg);
    ~ForkEmitChmFieldFromWeapon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m34(sead::Matrix34f* mtx) override;

    // 0x710014dfb0: the actor's matrix with the translation moved to the point below the weapon's
    // emission point (ray cast one unit up / down).
    void sub_710014DFB0(sead::Matrix34f* mtx);

    // static_param at offset 0xa8
    const int* mWeaponIdx_s{};
    // static_param at offset 0xb0
    const int* mSeqBank_s{};
    // static_param at offset 0xb8
    const int* mTargetBone_s{};
};

}  // namespace uking::action
