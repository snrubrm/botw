#include "Game/AI/Action/actionPlayerWaterDivingJump.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerWaterDivingJump::PlayerWaterDivingJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWaterDivingJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWaterDivingJump::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62C14(static_cast<ksys::act::Player*>(mActor)->_1800);
}

void PlayerWaterDivingJump::loadParams_() {
    getStaticParam(&mDiveSpeedF_s, "DiveSpeedF");
    getStaticParam(&mDiveHeight_s, "DiveHeight");
    getStaticParam(&mDiveSpeedDec_s, "DiveSpeedDec");
}

// NON_MATCHING: scheduling of the Matrix34f(_1b6c * _1b48) multiply (same operations: the zero translation terms are
// kept; the original needs fewer callee-saved d registers).
void PlayerWaterDivingJump::calc_() {
    mActor->getASList()->x_0(&static_cast<ksys::act::Player*>(mActor)->_19f0[0]);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_1b18 = player->_1b6c * sead::Matrix34f(player->_1b48);
    player = static_cast<ksys::act::Player*>(mActor);
    if (player->getVelocity().y < 0.0f) {
        const f32 zero = 0.0f;
        player->_20bc.chase(zero, *mDiveSpeedDec_s);
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerWaterDivingJump::isChangeable() const {
    return true;
}

bool PlayerWaterDivingJump::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround();
}

}  // namespace uking::action
