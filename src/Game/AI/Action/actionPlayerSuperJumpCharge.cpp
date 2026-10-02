#include "Game/AI/Action/actionPlayerSuperJumpCharge.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

PlayerSuperJumpCharge::PlayerSuperJumpCharge(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSuperJumpCharge::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSuperJumpCharge::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_1cbe = 0;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd4);
}

void PlayerSuperJumpCharge::loadParams_() {
    getStaticParam(&mChargeTime_s, "ChargeTime");
}

// NON_MATCHING: the two discarded ELink / SLink handles get separate stack slots in the original
void PlayerSuperJumpCharge::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();

    player = static_cast<ksys::act::Player*>(mActor);
    const f32 dx = player->_1810.x - player->_1770.x;
    const f32 dz = player->_1810.z - player->_1770.z;
    if (sead::Mathf::sqrt(dx * dx + dz * dz) > 2.0f ||
        static_cast<ksys::act::Player*>(mActor)->_1810.y -
                static_cast<ksys::act::Player*>(mActor)->_1770.y >
            1.1f) {
        setFailed();
        return;
    }

    player = static_cast<ksys::act::Player*>(mActor);
    if (player->_1cbe == 1)
        return;

    if (player->_1844.value > *mChargeTime_s) {
        player->_1cbe = 1;
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&static_cast<ksys::act::Player*>(mActor)->_2c78, &accessor) &&
            accessor.hasProc() && accessor.isStateSleep()) {
            accessor.setProperties(mActor->getMtx(), nullptr, nullptr, nullptr, false, 0, -1);
            ksys::eft::searchAndEmitELink(mActor, "Kago_Wind");
            ksys::eft::searchAndEmitSLink(mActor, "Kago_Wind", false);
        }
    }
    static_cast<ksys::act::Player*>(mActor)->_1844.update();
}

bool PlayerSuperJumpCharge::isChangeable() const {
    return true;
}

}  // namespace uking::action
