#include "Game/AI/AI/aiLynelRodeo.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

LynelRodeo::LynelRodeo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelRodeo::~LynelRodeo() = default;

bool LynelRodeo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelRodeo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelRodeo::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_80000000);
    *mLynelRodeoAttackHitNum_a = 0;
}

void LynelRodeo::loadParams_() {
    getAITreeVariable(&mLynelRodeoAttackHitNum_a, "LynelRodeoAttackHitNum");
}

}  // namespace uking::ai
