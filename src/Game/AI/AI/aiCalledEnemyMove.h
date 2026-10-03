#pragma once

#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CalledEnemyMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CalledEnemyMove, ksys::act::ai::Ai)
public:
    explicit CalledEnemyMove(const InitArg& arg);
    ~CalledEnemyMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void changeToApproach();
    // 0x7100341058 (placeholder name): the position the called enemy walks to (the target's position moved
    // along its forward vector by WaitDist); does nothing for a null `out`.
    void sub_7100341058(sead::Vector3f* out);
    // 0x7100340f4c (placeholder name)
    void changeToWait();

protected:
    // static_param at offset 0x38
    const float* mLostDist_s{};
    // static_param at offset 0x40
    const float* mWaitDist_s{};
    // dynamic_param at offset 0x48
    ksys::act::BaseProcLink* mTargetActor_d{};
    Unk_7102372510 _50{mActor, 0x8000008};
};

}  // namespace uking::ai
