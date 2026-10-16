#pragma once

#include "Game/Actor/Behavior/behaviorEnemyNeckRotate.h"

namespace uking::behavior {

class EnemyFrontNeckRotate : public EnemyNeckRotate {
    SEAD_RTTI_OVERRIDE(EnemyFrontNeckRotate, EnemyNeckRotate)
public:
    explicit EnemyFrontNeckRotate(const InitArg& arg);
    ~EnemyFrontNeckRotate() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    bool m14() override;

    /* 0x38 */ const float* mFrontAngleXZ_s{};
};
KSYS_CHECK_SIZE_NX150(EnemyFrontNeckRotate, 0x40);

}  // namespace uking::behavior
