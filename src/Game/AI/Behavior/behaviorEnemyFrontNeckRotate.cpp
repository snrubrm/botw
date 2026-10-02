#include "Game/AI/Behavior/behaviorEnemyFrontNeckRotate.h"

namespace uking::behavior {

EnemyFrontNeckRotate::EnemyFrontNeckRotate(const InitArg& arg) : EnemyNeckRotate(arg) {}

EnemyFrontNeckRotate::~EnemyFrontNeckRotate() = default;

bool EnemyFrontNeckRotate::m6(sead::Heap* heap) {
    return EnemyNeckRotate::m6(heap);
}

void EnemyFrontNeckRotate::m7() {
    EnemyNeckRotate::m7();
}

void EnemyFrontNeckRotate::m8() {
    EnemyNeckRotate::m8();
}

void EnemyFrontNeckRotate::m9() {
    EnemyNeckRotate::m9();
}

void EnemyFrontNeckRotate::loadParams() {
    EnemyNeckRotate::loadParams();
    getStaticParam(&mFrontAngleXZ_s, "FrontAngleXZ");
}

}  // namespace uking::behavior
