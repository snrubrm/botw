#pragma once

#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::ai {

class FishGoToAndNibble : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FishGoToAndNibble, ksys::act::ai::Ai)
public:
    explicit FishGoToAndNibble(const InitArg& arg);
    ~FishGoToAndNibble() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x71003cb38c / 0x71003cb4c0 (placeholder names): move to the target actor's position / to its position below
    // the fish's own center; fail if the target actor is gone.
    void changeToFinalMove();
    void changeToMove();

protected:
    // static_param at offset 0x38
    const int* mNumTimeNibbleMin_s{};
    // static_param at offset 0x40
    const int* mNumTimeNibbleRand_s{};
    // static_param at offset 0x48
    const float* mDistStartNibble_s{};
    // static_param at offset 0x50
    const float* mDistBackward_s{};
    // static_param at offset 0x58
    const float* mDepthGiveUp_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x68
    ksys::act::BaseProcLink* mTargetActor_d{};
    sead::Vector3f _70{0, 0, 0};
    ksys::Timer _7c{0, 0};
    sead::BoundBox3f _88;
    sead::BoundBox3f _a0;
    f32 _b8 = 0;
    ksys::phys::RigidBody* _c0 = nullptr;
    s8 _c8 = 0;
};

}  // namespace uking::ai
