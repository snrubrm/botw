#pragma once

#include "Game/AI/Action/actionUnk_7102451ba0.h"
#include "KingSystem/System/VFRValue.h"
#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class UnarmedAttack : public ActionEx {
    SEAD_RTTI_OVERRIDE(UnarmedAttack, ActionEx)
public:
    explicit UnarmedAttack(const InitArg& arg);
    ~UnarmedAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    virtual int m32();
    virtual float m33();
    virtual void m34();

    // static_param at offset 0x20
    const char* mASName_s{};
    // static_param at offset 0x28
    const char* mAtRigidBodyName_s{};
    // static_param at offset 0x30
    const float* mSpeed_s{};
    // static_param at offset 0x38
    const float* mRotAngle_s{};
    // static_param at offset 0x40
    const float* mSpeedStopRatio_s{};
    // static_param at offset 0x48
    const float* mRotSpeedStopRatio_s{};
    // static_param at offset 0x50
    const float* mJustAvoidCheckLength_s{};
    // static_param at offset 0x58
    const float* mJustAvoidCheckAngle_s{};
    // static_param at offset 0x60
    const bool* mIsIgnoreSmallHit_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
    Unk_7102451ba0 _70;
    ksys::VFRValue _98{0.0f};
    ksys::VFRVec3f _a4;
    sead::Vector3f _c8 = {0, 0, 0};
    f32 _d4 = 0;
    u32 _d8 = 0;
    s8 _dc = -1;
};

}  // namespace uking::action
