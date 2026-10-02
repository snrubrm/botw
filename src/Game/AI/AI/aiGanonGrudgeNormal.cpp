#include "Game/AI/AI/aiGanonGrudgeNormal.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
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

void GanonGrudgeNormal::m34() {
    if (mActor->getRootAi()->getI() == 5)
        EnemyNormal::m34();
    else
        changeChild("出現");
}

void GanonGrudgeNormal::m36() {
    if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000))
        changeChild("消失");
    else
        EnemyNormal::m36();
}

void GanonGrudgeNormal::m48(sead::Vector3f* pos) {
    pos->set(_3d0);
}

}  // namespace uking::ai
