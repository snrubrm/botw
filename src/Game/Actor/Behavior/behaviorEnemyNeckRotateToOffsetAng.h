#pragma once

#include "Game/Actor/Behavior/behaviorEnemyNeckRotate.h"

namespace uking::behavior {

class EnemyNeckRotateToOffsetAng : public EnemyNeckRotate {
    SEAD_RTTI_OVERRIDE(EnemyNeckRotateToOffsetAng, EnemyNeckRotate)
public:
    explicit EnemyNeckRotateToOffsetAng(const InitArg& arg);
    ~EnemyNeckRotateToOffsetAng() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void m15(sead::Vector3f* out) override;

    /* 0x38 */ const float* mAngleXZ_s{};
};
KSYS_CHECK_SIZE_NX150(EnemyNeckRotateToOffsetAng, 0x40);

}  // namespace uking::behavior
