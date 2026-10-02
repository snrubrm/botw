#include "Game/AI/Behavior/behaviorEnemyFrontNeckRotate.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

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

// NON_MATCHING: register naming of the two z loads (target.z / pos.z) of the direction subtraction
bool EnemyFrontNeckRotate::m14() {
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    front.y = 0;
    front.normalize();
    sead::Vector3f pos;
    sub_71005DB4B8(&pos, mActor);
    sead::Vector3f target;
    m15(&target);
    sead::Vector3f dir = target - pos;
    dir.y = 0;
    dir.normalize();
    return !(front.dot(dir) >= sead::Mathf::cos(*mFrontAngleXZ_s));
}

void EnemyFrontNeckRotate::loadParams() {
    EnemyNeckRotate::loadParams();
    getStaticParam(&mFrontAngleXZ_s, "FrontAngleXZ");
}

}  // namespace uking::behavior
