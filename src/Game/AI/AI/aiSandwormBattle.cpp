#include "Game/AI/AI/aiSandwormBattle.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SandwormBattle::SandwormBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormBattle::~SandwormBattle() = default;

bool SandwormBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    sub_7100557504();
}

void SandwormBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormBattle::loadParams_() {
    getStaticParam(&mAttackAngle_s, "AttackAngle");
    getStaticParam(&mAttackInterval_s, "AttackInterval");
    getStaticParam(&mAttackIntervalRand_s, "AttackIntervalRand");
    getStaticParam(&mBattleFailTimer_s, "BattleFailTimer");
}

}  // namespace uking::ai
