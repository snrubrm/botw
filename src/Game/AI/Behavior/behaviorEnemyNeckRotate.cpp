#include "Game/AI/Behavior/behaviorEnemyNeckRotate.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::behavior {

EnemyNeckRotate::EnemyNeckRotate(const InitArg& arg) : NeckControl(arg) {}

EnemyNeckRotate::~EnemyNeckRotate() = default;

bool EnemyNeckRotate::m6(sead::Heap* heap) {
    return NeckControl::m6(heap);
}

void EnemyNeckRotate::m7() {
    NeckControl::m7();
}

void EnemyNeckRotate::m8() {
    NeckControl::m8();
}

void EnemyNeckRotate::m9() {
    NeckControl::m9();
}

void EnemyNeckRotate::loadParams() {
    NeckControl::loadParams();
}

void EnemyNeckRotate::m15(sead::Vector3f* out) {
    ksys::act::ActorConstDataAccess accessor;
    const sead::Vector3f* pos;
    if (ksys::act::acquireActor(&sub_71005D94AC(mActor), &accessor))
        pos = &accessor.getPreviousPos2();
    else
        pos = &sub_71005D960C(mActor);
    out->set(*pos);
}

}  // namespace uking::behavior
