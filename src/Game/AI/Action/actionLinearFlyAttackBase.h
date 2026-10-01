#pragma once

#include "Game/AI/Action/actionUnk_7102451ba0.h"
#include <math/seadMatrix.h>
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LinearFlyAttackBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LinearFlyAttackBase, ksys::act::ai::Action)
public:
    explicit LinearFlyAttackBase(const InitArg& arg);
    ~LinearFlyAttackBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual int m32();
    virtual void m33(sead::Vector3f* dir);
    virtual f32 m34();

    // static_param at offset 0x20
    const int* mTime_s{};
    // static_param at offset 0x28
    const float* mAttackSpeed_s{};
    // static_param at offset 0x30
    const float* mAttackSlowDownRatio_s{};
    // static_param at offset 0x38
    const float* mTargetHeightOffset_s{};
    // static_param at offset 0x40
    const float* mThroughDist_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    Unk_7102451ba0 _50;
    sead::Matrix33f _78;
    f32 _9c = 0;
    f32 _a0 = 0;
    f32 _a4 = 0;
    sead::Vector3f _a8;
    f32 _b4 = 0;
    sead::Vector3f _b8;
    ksys::VFRValue _c4;
    bool _d0 = false;
};

}  // namespace uking::action
