#include "Game/AI/Behavior/behaviorEnemyNeckRotateToOffsetAng.h"

namespace uking::behavior {

EnemyNeckRotateToOffsetAng::EnemyNeckRotateToOffsetAng(const InitArg& arg) : EnemyNeckRotate(arg) {}

EnemyNeckRotateToOffsetAng::~EnemyNeckRotateToOffsetAng() = default;

bool EnemyNeckRotateToOffsetAng::m6(sead::Heap* heap) {
    return EnemyNeckRotate::m6(heap);
}

void EnemyNeckRotateToOffsetAng::m7() {
    EnemyNeckRotate::m7();
}

void EnemyNeckRotateToOffsetAng::m8() {
    EnemyNeckRotate::m8();
}

void EnemyNeckRotateToOffsetAng::m9() {
    EnemyNeckRotate::m9();
}

void EnemyNeckRotateToOffsetAng::loadParams() {
    EnemyNeckRotate::loadParams();
    getStaticParam(&mAngleXZ_s, "AngleXZ");
}

}  // namespace uking::behavior
