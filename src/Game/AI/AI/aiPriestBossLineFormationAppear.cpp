#include "Game/AI/AI/aiPriestBossLineFormationAppear.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PriestBossLineFormationAppear::PriestBossLineFormationAppear(const InitArg& arg)
    : SeqTwoAction(arg) {}

PriestBossLineFormationAppear::~PriestBossLineFormationAppear() = default;

bool PriestBossLineFormationAppear::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void PriestBossLineFormationAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void PriestBossLineFormationAppear::calc_() {
    SeqTwoAction::calc_();
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;

    if (isCurrentChild("先行動"))
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityGround);
    else
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
}

void PriestBossLineFormationAppear::leave_() {
    auto* controller = mActor->getCharacterController();
    if (controller)
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
}

void PriestBossLineFormationAppear::loadParams_() {
    SeqTwoAction::loadParams_();
}

}  // namespace uking::ai
