#include "Game/AI/AI/aiHorseRiddenByEnemyAI.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HorseRiddenByEnemyAI::HorseRiddenByEnemyAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRiddenByEnemyAI::~HorseRiddenByEnemyAI() = default;

bool HorseRiddenByEnemyAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRiddenByEnemyAI::enter_(ksys::act::ai::InlineParamPack* params) {
    _60.reset();
    _70 = 0;
    _74 = -1.0f;
    _78 = false;
    changeChild("通常");
}

void HorseRiddenByEnemyAI::leave_() {
    if (auto* rideable = mActor->getHorseOptionsMaybe())
        rideable->m22(0);
}

void HorseRiddenByEnemyAI::loadParams_() {
    getStaticParam(&mAngryASPeriods_s, "AngryASPeriods");
    getStaticParam(&mFramesRetryNormalActionAtFailed_s, "FramesRetryNormalActionAtFailed");
}

}  // namespace uking::ai
