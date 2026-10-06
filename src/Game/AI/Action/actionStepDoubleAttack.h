#pragma once

#include "Game/AI/Action/actionUnk_7102451ba0.h"
#include <math/seadMatrix.h>
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StepDoubleAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(StepDoubleAttack, ksys::act::ai::Action)
public:
    explicit StepDoubleAttack(const InitArg& arg);
    ~StepDoubleAttack() override = default;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    virtual int m32();
    virtual void m33(int weapon_idx, const sead::SafeString* name, bool a3, f32 a4);

    struct Params {
        // static_param at offset 0x20
        const int* mWeaponIdx_s{};
        // static_param at offset 0x28
        const float* mCloseDist_s{};
        // static_param at offset 0x30
        const float* mSpeed_s{};
        // static_param at offset 0x38
        const float* mRotSpd_s{};
        // static_param at offset 0x40
        const float* mJustAvoidSideDist_s{};
        // static_param at offset 0x48
        const float* mJustAvoidBackDist_s{};
        // static_param at offset 0x50
        const float* mJustAvoidAngle_s{};
        // dynamic_param at offset 0x58
        sead::Vector3f* mTargetPos_d{};
    };
    Params mParams;
    Unk_7102451ba0 _60;
    ksys::VFRValue _88{0.0f};
    f32 _94 = 0;
    sead::Matrix33f _98;
    sead::Vector3f _bc = {0, 0, 0};
    int _c8 = 0;
};

}  // namespace uking::action
