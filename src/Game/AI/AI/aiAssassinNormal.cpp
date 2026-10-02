#include "Game/AI/AI/aiAssassinNormal.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

AssassinNormal::AssassinNormal(const InitArg& arg) : LandHumEnemyNormal(arg) {}

AssassinNormal::~AssassinNormal() = default;

bool AssassinNormal::init_(sead::Heap* heap) {
    return LandHumEnemyNormal::init_(heap);
}

void AssassinNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyNormal::enter_(params);
    mActor->getMtx().getTranslation(_410);
    _400.reset();
}

void AssassinNormal::calc_() {
    LandHumEnemyNormal::calc_();
}

void AssassinNormal::leave_() {
    LandHumEnemyNormal::leave_();
}

void AssassinNormal::loadParams_() {
    LandHumEnemyNormal::loadParams_();
}

s32 AssassinNormal::m53() {
    return 12;
}

}  // namespace uking::ai
