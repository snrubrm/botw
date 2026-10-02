#include "Game/AI/Action/actionPriestBossBlownOff.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PriestBossBlownOff::PriestBossBlownOff(const InitArg& arg) : BlownOff(arg) {}

PriestBossBlownOff::~PriestBossBlownOff() = default;

void PriestBossBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    BlownOff::enter_(params);
    _15d = false;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F605F0();
}

void PriestBossBlownOff::leave_() {
    BlownOff::leave_();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F60604();
}

void PriestBossBlownOff::loadParams_() {
    BlownOff::loadParams_();
}

void PriestBossBlownOff::calc_() {
    BlownOff::calc_();
}

}  // namespace uking::action
