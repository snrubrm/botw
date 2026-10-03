#include "Game/AI/Behavior/behaviorEnemyNeckRotateToOffsetAng.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/Utils/MathUtil.h"

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

// NON_MATCHING: operand order of the final `out + rotated` additions (the original adds `out` first)
void EnemyNeckRotateToOffsetAng::m15(sead::Vector3f* out) {
    auto* unit = ksys::act::sub_7100D82FFC(mActor->getBoneControl());
    if (!unit) {
        EnemyNeckRotate::m15(out);
        return;
    }
    unit->sub_7100D88CF4(out);
    sead::Vector3f direction = sead::Vector3f::ez * 100.0f;
    ksys::util::sub_71011EF010(&direction, *mAngleXZ_s);
    sead::Vector3f rotated;
    rotated.setRotated(mActor->getMtx(), direction);
    *out += rotated;
}

void EnemyNeckRotateToOffsetAng::loadParams() {
    EnemyNeckRotate::loadParams();
    getStaticParam(&mAngleXZ_s, "AngleXZ");
}

}  // namespace uking::behavior
