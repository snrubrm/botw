#pragma once

#include "Game/AI/Behavior/behaviorEnemyNeckRotate.h"

namespace uking::behavior {

class EnemyFrontNeckRotate : public EnemyNeckRotate {
    SEAD_RTTI_OVERRIDE(EnemyFrontNeckRotate, EnemyNeckRotate)
public:
    explicit EnemyFrontNeckRotate(const InitArg& arg);
    ~EnemyFrontNeckRotate() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    bool m14() override;  // TODO 0x710062118c

    /* 0x38 */ const float* mFrontAngleXZ_s{};
};
KSYS_CHECK_SIZE_NX150(EnemyFrontNeckRotate, 0x40);

}  // namespace uking::behavior
