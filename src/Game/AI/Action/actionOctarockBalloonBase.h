#pragma once

#include "Game/AI/Action/actionBalloonBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

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

public:
    // 0xb8928: out of line in the original. Public because Balloon::init_ calls it directly on its
    // own object (via BalloonBase); it only reads Action+0x8, which has the same layout.
    void sub_71000B8928(f32 value);

protected:
    void calc_() override;
    float m33() override;
    f32 m34(f32 current, f32 target, f32 step) override;
    void m35(ksys::phys::RigidBody* a, ksys::phys::RigidBody* b, ksys::act::RopeBase* rope) override;

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
    /* 0x128 */ ksys::Timer _128;
};
KSYS_CHECK_SIZE_NX150(OctarockBalloonBase, 0x138);

}  // namespace uking::action
