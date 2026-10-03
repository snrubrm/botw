#pragma once

#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class GiantNavMoveTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GiantNavMoveTarget, ksys::act::ai::Ai)
public:
    explicit GiantNavMoveTarget(const InitArg& arg);
    ~GiantNavMoveTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();

    // 0x71003f78f4 / 0x71003f7da8 (placeholder names): changeChild("見まわす"); and the repath: restarts the repath
    // timer and asks the navigation for a reachable point near the target.
    void sub_71003F78F4();
    // 0x71003f7c20: resets the navigation state and the repath timer, then changeChild("%s") with the target.
    void sub_71003F7C20();
    void sub_71003F7DA8();

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mReachTargetArea_s{};
    // static_param at offset 0x48
    const float* mRepathTime_s{};
    // static_param at offset 0x50
    const float* mTooFarDist_s{};
    // static_param at offset 0x58
    const float* mTargetVMax_s{};
    // static_param at offset 0x60
    const float* mTargetVMin_s{};
    // static_param at offset 0x68
    const float* mFrontAngle_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
    // Result of sub_71005E2BCC (enter_): the actor's Enemy::_12d0.
    act::Enemy::Unk_12d0* _78{};
    ksys::Timer _80;
};

}  // namespace uking::ai
