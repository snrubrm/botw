#pragma once

#include "Game/AI/Action/actionBalloonBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OctarockBalloonBase : public BalloonBase {
    SEAD_RTTI_OVERRIDE(OctarockBalloonBase, BalloonBase)
public:
    explicit OctarockBalloonBase(const InitArg& arg);
    ~OctarockBalloonBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0xb8928 (declared only): out of line in the original.
    void sub_71000B8928(f32 value);
    void calc_() override;
    float m33() override;
    f32 m34(f32 current, f32 target, f32 step) override;

    // static_param at offset 0xf0
    const float* mConnectReleaseTimer_s{};
    // static_param at offset 0xf8
    const float* mClampWindForceScale_s{};
    // static_param at offset 0x100
    const float* mReduceVel_s{};
    // dynamic_param at offset 0x108
    sead::SafeString mConnectRigidName_d{};
    // dynamic_param at offset 0x118
    sead::Vector3f* mConnectRigidOffset_d{};
    // dynamic_param at offset 0x120
    ksys::act::BaseProcHandle** mRopeActorHandle_d{};
    /* 0x128 */ void* _128 = nullptr;
    /* 0x130 */ u32 _130 = 0;
};
KSYS_CHECK_SIZE_NX150(OctarockBalloonBase, 0x138);

}  // namespace uking::action
