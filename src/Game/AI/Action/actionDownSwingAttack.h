#pragma once

#include "Game/AI/Action/actionUnk_7102451ba0.h"
#include <math/seadMatrix.h>
#include "KingSystem/System/VFRValue.h"
#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DownSwingAttack : public ActionEx {
    SEAD_RTTI_OVERRIDE(DownSwingAttack, ActionEx)
public:
    explicit DownSwingAttack(const InitArg& arg);
    ~DownSwingAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpeed_s{};
    // static_param at offset 0x28
    const float* mStopSpeedRatio_s{};
    // static_param at offset 0x30
    const float* mStopRotSpeedRatio_s{};
    // static_param at offset 0x38
    const float* mJustAvoidCheckLength_s{};
    // static_param at offset 0x40
    const float* mJustAvoidCheckAngle_s{};
    // static_param at offset 0x48
    const int* mLoopTime_s{};
    // static_param at offset 0x50
    const int* mLoopTimeRand_s{};
    // static_param at offset 0x58
    const int* mWeaponIdx_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x68
    const bool* mIsSpecialAttack_s{};
    // static_param at offset 0x70
    const float* mSpecialAttackRadius_s{};
    // static_param at offset 0x78
    const float* mSpineControlOffsetY_s{};
    Unk_7102451ba0 _80;
    sead::Matrix33f _a8;
    ksys::VFRValue _cc{0.0f};
    ksys::VFRValue _d8{0.0f};
    f32 _e4 = 0;
    f32 _e8 = 0;
    f32 _ec = -1.0f;
    bool _f0 = false;
    bool _f1 = false;
    bool _f2 = false;
    sead::Vector3f _f4 = {0, 0, 0};
    int _100 = -1;
};

}  // namespace uking::action
