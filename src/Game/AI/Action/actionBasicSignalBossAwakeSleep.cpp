#include "Game/AI/Action/actionBasicSignalBossAwakeSleep.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BasicSignalBossAwakeSleep::BasicSignalBossAwakeSleep(const InitArg& arg) : BasicSignalEnemy(arg) {}

BasicSignalBossAwakeSleep::~BasicSignalBossAwakeSleep() = default;

bool BasicSignalBossAwakeSleep::init_(sead::Heap* heap) {
    return BasicSignalEnemy::init_(heap);
}

void BasicSignalBossAwakeSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    BasicSignalEnemy::enter_(params);
}

void BasicSignalBossAwakeSleep::leave_() {
    mActor->emitBasicSigOff();
    BasicSignalEnemy::leave_();
}

void BasicSignalBossAwakeSleep::loadParams_() {
    BasicSignalEnemy::loadParams_();
}

void BasicSignalBossAwakeSleep::calc_() {
    BasicSignalEnemy::calc_();
}

}  // namespace uking::action
