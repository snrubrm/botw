#pragma once

#include "Game/AI/Behavior/behaviorEnemyNeckRotate.h"

namespace uking::behavior {

class EnemyNeckRotateToOffsetAng : public EnemyNeckRotate {
    SEAD_RTTI_OVERRIDE(EnemyNeckRotateToOffsetAng, EnemyNeckRotate)
public:
    explicit EnemyNeckRotateToOffsetAng(const InitArg& arg);
    ~EnemyNeckRotateToOffsetAng() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m15(sead::Vector3f* out) override;

    /* 0x38 */ const float* mAngleXZ_s{};
};
KSYS_CHECK_SIZE_NX150(EnemyNeckRotateToOffsetAng, 0x40);

}  // namespace uking::behavior
