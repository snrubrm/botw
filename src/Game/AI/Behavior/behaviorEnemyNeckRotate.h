#pragma once

#include "Game/AI/Behavior/behaviorNeckControl.h"

namespace uking::behavior {

class EnemyNeckRotate : public NeckControl {
    SEAD_RTTI_OVERRIDE(EnemyNeckRotate, NeckControl)
public:
    explicit EnemyNeckRotate(const InitArg& arg);
    ~EnemyNeckRotate() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m15(sead::Vector3f* out) override;

};
KSYS_CHECK_SIZE_NX150(EnemyNeckRotate, 0x38);

}  // namespace uking::behavior
