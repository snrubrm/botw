#include "Game/AI/AI/aiCalledEnemyMove.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

CalledEnemyMove::CalledEnemyMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CalledEnemyMove::~CalledEnemyMove() = default;

bool CalledEnemyMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CalledEnemyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CalledEnemyMove::leave_() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    _50.x(mActor);
    _50.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
}

void CalledEnemyMove::loadParams_() {
    getStaticParam(&mLostDist_s, "LostDist");
    getStaticParam(&mWaitDist_s, "WaitDist");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
