#pragma once

#include <math/seadVector.h>

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class AnimalRushAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AnimalRushAttack, ksys::act::ai::Ai)
public:
    explicit AnimalRushAttack(const InitArg& arg);
    ~AnimalRushAttack() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x710030cb64 (placeholder name)
    bool sub_710030CB64(bool force);

protected:
    // static_param at offset 0x38
    const int* mUpdateTargetPosTime_s{};
    // static_param at offset 0x40
    const float* mAttackPosOffsetLength_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _50;
    sead::Vector3f _5c;
    bool _68 = false;
};

}  // namespace uking::ai
