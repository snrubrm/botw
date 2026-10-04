#pragma once

#include "KingSystem/System/VFRValue.h"
#include "Game/AI/Action/actionBackStepBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackStepAttack : public BackStepBase {
    SEAD_RTTI_OVERRIDE(BackStepAttack, BackStepBase)
public:
    explicit BackStepAttack(const InitArg& arg);
    ~BackStepAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m34() override;
    void m35() override;
    void m36() override;
    void m37() override;
    void m40() override;
    // 0x71000b362c (out of line in the original; name is a guess): starts the just-avoid attack move.
    void sub_71000B362C();

    ksys::VFRValue _c8{0.0f};
    Unk_7102451ba0 _d8;
    sead::Vector3f _100 = {0, 0, 0};
    f32 _10c = 0;
    // static_param at offset 0x110
    const int* mWeaponIdx_s{};
    // static_param at offset 0x118
    const float* mMoveDist_s{};
    // static_param at offset 0x120
    const float* mJustAvoidSideDist_s{};
    // static_param at offset 0x128
    const float* mJustAvoidBackDist_s{};
    // static_param at offset 0x130
    const float* mJustAvoidAngle_s{};
    int _138 = -1;
};

}  // namespace uking::action
