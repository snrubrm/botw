#include "Game/AI/Action/actionPlayerTwiceJump.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerTwiceJump::PlayerTwiceJump(const InitArg& arg) : PlayerFall(arg) {}

void PlayerTwiceJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerFall::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x20000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EF08(true);
        controller->sub_7100F62B70(
            *mJumpHeight_s * static_cast<ksys::act::Player*>(mActor)->getStatusEffectSpeed());
    }
    static_cast<ksys::act::Player*>(mActor)->_1ec0 = ksys::Timer(4.0f, 4.0f);
}

void PlayerTwiceJump::leave_() {}

void PlayerTwiceJump::loadParams_() {
    PlayerFall::loadParams_();
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerTwiceJump::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_7100881418();
    PlayerFall::calc_();
    if (static_cast<ksys::act::Player*>(mActor)->m179()) {
        static_cast<ksys::act::Player*>(mActor)->sub_71008824AC(false);
        auto* p = static_cast<ksys::act::Player*>(mActor);
        if (p->_d30 == p->getEquipmentTypeName(0)) {
            if (!p->_c40.isOnBit(3)) {
                setFinished();
                return;
            }
        }
        if (ksys::act::playerIsReloadingOrChargingOrShootingBow(static_cast<ksys::act::Player*>(mActor)))
            static_cast<ksys::act::Player*>(mActor)->x_37();
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerTwiceJump::isChangeable() const {
    return true;
}

bool PlayerTwiceJump::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround();
}

}  // namespace uking::action
