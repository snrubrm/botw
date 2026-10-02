#include "Game/AI/AI/aiGanonGrudgeNormal.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GanonGrudgeNormal::GanonGrudgeNormal(const InitArg& arg) : EnemyNormal(arg) {}

GanonGrudgeNormal::~GanonGrudgeNormal() = default;

bool GanonGrudgeNormal::init_(sead::Heap* heap) {
    if (!EnemyNormal::init_(heap))
        return false;
    mActor->getMtx().getTranslation(_3d0);
    return true;
}

void GanonGrudgeNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void GanonGrudgeNormal::leave_() {
    EnemyNormal::leave_();
}

void GanonGrudgeNormal::loadParams_() {
    EnemyNormal::loadParams_();
}

void GanonGrudgeNormal::calc_() {
    if (isCurrentChild("出現"))
        mActor->getMtx().getTranslation(_3d0);
    if (!isCurrentChild("消失"))
        EnemyNormal::calc_();
}

}  // namespace uking::ai
