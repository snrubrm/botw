#include "Game/AI/AI/aiPriestBossCircleFormationRush.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PriestBossCircleFormationRush::PriestBossCircleFormationRush(const InitArg& arg)
    : PriestBossFormation(arg) {}

PriestBossCircleFormationRush::~PriestBossCircleFormationRush() = default;

bool PriestBossCircleFormationRush::init_(sead::Heap* heap) {
    return PriestBossFormation::init_(heap);
}

void PriestBossCircleFormationRush::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossFormation::enter_(params);
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
    m43();
}

void PriestBossCircleFormationRush::leave_() {
    PriestBossFormation::leave_();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F60604();
}

void PriestBossCircleFormationRush::loadParams_() {
    PriestBossFormation::loadParams_();
    getStaticParam(&mHomingAttackTime_s, "HomingAttackTime");
}

bool PriestBossCircleFormationRush::m36() {
    if (isCurrentChild("陣形作成後待機"))
        return false;
    return PriestBossFormation::m36();
}

}  // namespace uking::ai
