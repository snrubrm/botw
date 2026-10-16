#include "Game/Actor/Behavior/behaviorEnemyFrontNeckRotate.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

EnemyFrontNeckRotate::EnemyFrontNeckRotate(const InitArg& arg) : EnemyNeckRotate(arg) {}

EnemyFrontNeckRotate::~EnemyFrontNeckRotate() = default;

bool EnemyFrontNeckRotate::init_(sead::Heap* heap) {
    return EnemyNeckRotate::init_(heap);
}

void EnemyFrontNeckRotate::calc() {
    EnemyNeckRotate::calc();
}

void EnemyFrontNeckRotate::enter() {
    EnemyNeckRotate::enter();
}

void EnemyFrontNeckRotate::leave() {
    EnemyNeckRotate::leave();
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
