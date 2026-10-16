#include "Game/Actor/Behavior/behaviorEnemyNeckRotate.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcAccessor.h"

namespace uking::behavior {

EnemyNeckRotate::EnemyNeckRotate(const InitArg& arg) : NeckControl(arg) {}

EnemyNeckRotate::~EnemyNeckRotate() = default;

bool EnemyNeckRotate::init_(sead::Heap* heap) {
    return NeckControl::init_(heap);
}

void EnemyNeckRotate::calc() {
    NeckControl::calc();
}

void EnemyNeckRotate::enter() {
    NeckControl::enter();
}

void EnemyNeckRotate::leave() {
    NeckControl::leave();
}

void EnemyNeckRotate::loadParams() {
    NeckControl::loadParams();
}

void EnemyNeckRotate::m15(sead::Vector3f* out) {
    ksys::act::ActorLinkConstDataAccess accessor;
    const sead::Vector3f* pos;
    if (ksys::act::acquireActor(&sub_71005D94AC(mActor), &accessor))
        pos = &accessor.getPreviousPos2();
    else
        pos = &sub_71005D960C(mActor);
    out->set(*pos);
}

}  // namespace uking::behavior
