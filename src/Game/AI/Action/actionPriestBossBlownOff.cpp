#include "Game/AI/Action/actionPriestBossBlownOff.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Damage/dmgDamageManager.h"
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
    if (!_15d && mActor->getMtx()(1, 1) < 0.70710677f && m34()) {
        xlinkSearchAndEmit(mActor, "Down", 2, nullptr);
        _15d = true;
    }
}

s32 PriestBossBlownOff::m41(uking::dmg::DamageManager* manager) {
    if (!isBgGroundHit(mActor, false) && manager->getField50() == 8)
        return 12;
    return manager->getField50();
}

}  // namespace uking::action
