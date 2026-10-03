#include "Game/AI/AI/aiEnemyHorseRide.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

EnemyHorseRide::EnemyHorseRide(const InitArg& arg) : NonPlayerHorseRide(arg) {}

EnemyHorseRide::~EnemyHorseRide() = default;

bool EnemyHorseRide::init_(sead::Heap* heap) {
    return NonPlayerHorseRide::init_(heap);
}

void EnemyHorseRide::enter_(ksys::act::ai::InlineParamPack* params) {
    NonPlayerHorseRide::enter_(params);
}

void EnemyHorseRide::leave_() {
    NonPlayerHorseRide::leave_();
}

void EnemyHorseRide::loadParams_() {
    NonPlayerHorseRide::loadParams_();
    getStaticParam(&mUpperBodyASSlot_s, "UpperBodyASSlot");
    getStaticParam(&mLowerBodyASSlot_s, "LowerBodyASSlot");
}

bool EnemyHorseRide::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003)
        m34();
    return false;
}

void EnemyHorseRide::m34() {
    if (mActor->isDelete())
        return;
    NonPlayerHorseRide::m34();
}

}  // namespace uking::ai
