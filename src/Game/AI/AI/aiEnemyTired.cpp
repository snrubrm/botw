#include "Game/AI/AI/aiEnemyTired.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyTired::EnemyTired(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyTired::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    changeChild("見まわす");
}

void EnemyTired::loadParams_() {}

}  // namespace uking::ai
