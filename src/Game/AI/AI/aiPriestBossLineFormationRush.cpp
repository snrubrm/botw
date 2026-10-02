#include "Game/AI/AI/aiPriestBossLineFormationRush.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PriestBossLineFormationRush::PriestBossLineFormationRush(const InitArg& arg)
    : PriestBossFormation(arg) {}

PriestBossLineFormationRush::~PriestBossLineFormationRush() = default;

bool PriestBossLineFormationRush::init_(sead::Heap* heap) {
    return PriestBossFormation::init_(heap);
}

void PriestBossLineFormationRush::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossFormation::enter_(params);
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
    m43();
}

void PriestBossLineFormationRush::leave_() {
    PriestBossFormation::leave_();
}

void PriestBossLineFormationRush::loadParams_() {
    PriestBossFormation::loadParams_();
}

}  // namespace uking::ai
