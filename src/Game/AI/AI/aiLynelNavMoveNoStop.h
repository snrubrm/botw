#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class LynelNavMoveNoStop : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelNavMoveNoStop, ksys::act::ai::Ai)
public:
    explicit LynelNavMoveNoStop(const InitArg& arg);
    ~LynelNavMoveNoStop() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();
    virtual bool m35();

    void sub_71004923C0();
    // 0x7100492574 (placeholder names for the helpers 0x7100492574-0x71004930d0, called by LynelNavMoveTarget):
    // paths to `*mTargetPos_d` and restarts the repath timer.
    void sub_7100492574();
    // 0x7100492cb8: the nav mesh character's state is 1 (false if there is none).
    bool sub_7100492CB8();
    // 0x7100492ddc: the nav mesh character's state is 3 (true if there is none).
    bool sub_7100492DDC();
    // 0x7100493058: counts the repath timer down and re-paths when it has run out.
    void sub_7100493058();
    // 0x7100492e34: the target is within 45 degrees of the actor's front (both projected onto the ground plane).
    bool sub_7100492E34();
    // 0x71004930d0: gives the current child the target position.
    void sub_71004930D0();
    // 0x71004925c0 (placeholder name)
    void changeToGoStraight();
    // 0x7100492d10 (placeholder name)
    void changeToMove();

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mReachTargetArea_s{};
    // static_param at offset 0x48
    const float* mRepathTime_s{};
    // static_param at offset 0x50
    const float* mTooFarDist_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _60;
};

}  // namespace uking::ai
