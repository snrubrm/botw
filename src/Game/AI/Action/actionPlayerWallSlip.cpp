#include "Game/AI/Action/actionPlayerWallSlip.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerWallSlip::PlayerWallSlip(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWallSlip::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x200000);
    const u32 angle = static_cast<ksys::act::Player*>(mActor)->_1c84 ^ 0x80000000;
    static_cast<ksys::act::Player*>(mActor)->_1834 =
        ksys::util::Unk_7101EC6BAC(ksys::util::sUnk_7101EC6BA0 & angle);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("ClimbNG", true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->_1c68 = static_cast<ksys::act::Player*>(mActor)->_1834;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value *= 0.5f;
    player->_20bc.prev_value = player->_20bc.value;
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EF08(true);
        controller->sub_7100F62B70(*mJumpHeight_s * static_cast<ksys::act::Player*>(mActor)->getStatusEffectSpeed());
    }
    static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
}

void PlayerWallSlip::leave_() {}

void PlayerWallSlip::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerWallSlip::calc_() {
    PlayerAction::calc_();
}

bool PlayerWallSlip::isChangeable() const {
    return _1c;
}

bool PlayerWallSlip::isFinished() const {
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        return true;
    return mActor->getASList()->x_4(0, 0);
}

}  // namespace uking::action
