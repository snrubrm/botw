#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class ArrowShootMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ArrowShootMove, ksys::act::ai::Action)
public:
    explicit ArrowShootMove(const InitArg& arg);
    ~ArrowShootMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual float m32();
    virtual void m33();

    // dynamic_param at offset 0x20
    bool* mIsShootByPlayer_d{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mFirstSpeed_d{};
    // dynamic_param at offset 0x30
    float* mAccel_d{};
    // dynamic_param at offset 0x38
    float* mAimSpeed_d{};
    // dynamic_param at offset 0x40
    float* mFallAccel_d{};
    // dynamic_param at offset 0x48
    float* mFallAimSpeed_d{};
    // dynamic_param at offset 0x50
    float* mGravity_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x60
    float* mAtPoint_d{};
    // dynamic_param at offset 0x68
    float* mAtRange_d{};
    // dynamic_param at offset 0x70
    float* mAtImpulse_d{};
    // dynamic_param at offset 0x78
    float* mAtImpact_d{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mRelativeVel_d{};
    // dynamic_param at offset 0x88
    int* mAtAttr_d{};
    // dynamic_param at offset 0x90
    int* mAtMinDamage_d{};
    // static_param at offset 0x98
    const float* mFallSpeedRatioByRange_s{};
    // zero-initialised by the ctor (contents unknown)
    u8 _a0[0xb4 - 0xa0]{};
    ksys::VFRValue _b4{0.0f};
    ksys::VFRVec3f _c0;
    // zero-initialised by the ctor (contents unknown)
    u8 _e4[0x134 - 0xe4]{};
    void* _138 = nullptr;
    s8 _140 = -1;
    u32 _144 = 0;
    u8 _148 = 0;
    u8 _149 = 0;
    u8 _14a = 0;
};

KSYS_CHECK_SIZE_NX150(ArrowShootMove, 0x150);

}  // namespace uking::action
