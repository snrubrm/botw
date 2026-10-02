#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::ai {

class GoronCannonBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GoronCannonBase, ksys::act::ai::Ai)
public:
    explicit GoronCannonBase(const InitArg& arg);
    ~GoronCannonBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    void sub_710032D5FC();

    virtual void m35(ksys::act::Actor* actor, ksys::act::Actor* ball);
    virtual void m36(ksys::act::Actor* ball);

protected:
    // static_param at offset 0x38
    const float* mRotRadAccel_s{};
    // static_param at offset 0x40
    const float* mRotBrake_s{};
    // static_param at offset 0x48
    const float* mShotCannonBallScale_s{};
    // static_param at offset 0x50
    const bool* mIsDrawDebug_s{};
    // static_param at offset 0x58
    const bool* mIsUseShotNodeAngle_s{};
    // static_param at offset 0x60
    sead::SafeString mActName_s{};
    // static_param at offset 0x70
    sead::SafeString mShotNodeName_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mOffset_s{};
    // map_unit_param at offset 0x88
    const float* mTiltAngle_m{};
    // map_unit_param at offset 0x90
    const float* mTiltAngularSpeed_m{};
    // map_unit_param at offset 0x98
    const float* mAngle_m{};
    // map_unit_param at offset 0xa0
    const float* mSpeed_m{};
    // map_unit_param at offset 0xa8
    sead::SafeString mActorName_m{};
    ksys::act::BaseProcHandle _b8;
    void* _c8 = nullptr;
    u32 _d0 = 0;
    void* _d8 = nullptr;
    u32 _e0 = 0;
    u32 _e4;
    sead::Vector3f _e8 = sead::Vector3f::ey;
    s32 _f4 = -1;
    f32 _f8 = 0;
    f32 _fc = 0;
    f32 _100 = 0;
    f32 _104 = 0;
    bool _108 = false;
    bool _109 = false;
    bool _10a = false;
    bool _10b = false;
    sead::Vector3f _10c = sead::Vector3f::zero;
    sead::Vector3f _118 = sead::Vector3f::zero;
    f32 _124 = 0;
    f32 _128 = 0;
    bool _12c = false;
    bool _12d = false;
};
KSYS_CHECK_SIZE_NX150(GoronCannonBase, 0x130);

}  // namespace uking::ai
