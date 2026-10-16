#include "Game/Actor/Behavior/behaviorEnemyNeckRotateToOffsetAng.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::behavior {

EnemyNeckRotateToOffsetAng::EnemyNeckRotateToOffsetAng(const InitArg& arg) : EnemyNeckRotate(arg) {}

EnemyNeckRotateToOffsetAng::~EnemyNeckRotateToOffsetAng() = default;

bool EnemyNeckRotateToOffsetAng::init_(sead::Heap* heap) {
    return EnemyNeckRotate::init_(heap);
}

void EnemyNeckRotateToOffsetAng::calc() {
    EnemyNeckRotate::calc();
}

void EnemyNeckRotateToOffsetAng::enter() {
    EnemyNeckRotate::enter();
}

void EnemyNeckRotateToOffsetAng::leave() {
    EnemyNeckRotate::leave();
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
