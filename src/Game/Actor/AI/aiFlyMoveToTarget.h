#pragma once

#include <container/seadRingBuffer.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class FlyMoveToTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FlyMoveToTarget, ksys::act::ai::Ai)
public:
    explicit FlyMoveToTarget(const InitArg& arg);
    ~FlyMoveToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    void sub_71003D4414();
    // 0x71003d5108 (placeholder name)
    void changeToMoveFar();
    // 0x71003d5204 (placeholder name)
    void changeToMoveOnNavMesh();
    // 0x71003d501c (placeholder name)
    void changeToViaPointMove();
    // 0x71003d4ef0 (placeholder name): restarts the via point list with the target and moves to it.
    void changeToTargetPosMove();
    // 0x71003d53e0 (placeholder name): descends above the actor's position to `height`.
    void changeToDescend(f32 height);
    // 0x71003d4c84 (placeholder name): while the target (raised by OffsetHeight) is hidden, adds it as a via point
    // when it moved more than 0.5 from the last one and that one sees it; while visible and moving to the target
    // position, updates the first via point.
    void sub_71003D4C84();

protected:
    // static_param at offset 0x38
    const int* mMoveFailCount_s{};
    // static_param at offset 0x40
    const float* mFarDist_s{};
    // static_param at offset 0x48
    const float* mOutDist_s{};
    // static_param at offset 0x50
    const float* mOffsetHeight_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    sead::FixedRingBuffer<sead::Vector3f, 3> _60;
    sead::Vector3f _98;
    bool _a4{};
    ksys::Timer _a8;
    u32 _b4{};
};

}  // namespace uking::ai
