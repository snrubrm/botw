#pragma once

#include <math/seadVector.h>

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class AnimalBattleMoveLeave : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AnimalBattleMoveLeave, ksys::act::ai::Ai)
public:
    explicit AnimalBattleMoveLeave(const InitArg& arg);
    ~AnimalBattleMoveLeave() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100303a90 (placeholder name; declared only)
    void sub_7100303A90();

protected:
    // static_param at offset 0x38
    const float* mCheckForwardDist_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _48;
    sead::Vector3f _54;
    sead::Vector3f _60{0, 0, 0};
    s32 _6c = 0;
};

}  // namespace uking::ai
