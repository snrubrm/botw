#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class EnemyEscape : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyEscape, ksys::act::ai::Ai)
public:
    explicit EnemyEscape(const InitArg& arg);
    ~EnemyEscape() override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;

protected:
    sead::Vector3f* mTargetPos_d{};
    const int* mTumbleTime_s{};
    const int* mTumbleRand_s{};
    const int* mEscapeTime_s{};
    const int* mEscapeRand_s{};
    const float* mEscapeDist_s{};
    ksys::Timer _68{0, 0};
    bool _74{};
    ksys::Timer _78;
};

}  // namespace uking::ai
