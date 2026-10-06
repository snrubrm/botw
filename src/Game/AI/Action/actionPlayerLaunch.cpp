#include "Game/AI/Action/actionPlayerLaunch.h"
#include "Game/gameRumble.h"
#include "Game/gameUnk_71008ba8d8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerLaunch::PlayerLaunch(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLaunch::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x2000000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x8);
    if (static_cast<ksys::act::Player*>(mActor)->stillAlive()) {
        static_cast<ksys::act::Player*>(mActor)->x_16();
        static_cast<ksys::act::Player*>(mActor)->m228(false);
        const f32 jump_height = *mJumpHeight_s;
        const f32 init_speed = *mInitSpeed_s;
        auto* player = static_cast<ksys::act::Player*>(mActor);
        player->_1844 = ksys::Timer(*mNoRagdollTime_s, *mNoRagdollTime_s);
        player = static_cast<ksys::act::Player*>(mActor);
        player->_20bc.value = init_speed;
        player->_20bc.prev_value = init_speed;
        if (auto* controller = mActor->getCharacterController()) {
            controller->sub_7100F5EF08(true);
            controller->sub_7100F62B70(jump_height);
        }
        static_cast<ksys::act::Player*>(mActor)->_1800 = *mAddLinearImpulse_s;
        static_cast<ksys::act::Player*>(mActor)->_1804 = *mAddRollImpulse_s;
        static_cast<ksys::act::Player*>(mActor)->_1c68 = ksys::util::Unk_7101EC6BAC(sead::Mathf::atan2Idx(
            static_cast<ksys::act::Player*>(mActor)->_1770.x - mBasePos_d->x,
            static_cast<ksys::act::Player*>(mActor)->_1770.z - mBasePos_d->z));
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DamageL", true, -1.0f);
        Rumble::instance()->sub_7100897FE4(1, 1);
        static_cast<ksys::act::Player*>(mActor)->ksys::act::Player::m369(*mDamage_s);
    } else {
        static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x100);
        if (static_cast<ksys::act::Player*>(mActor)->isRidingHorse()) {
            static_cast<ksys::act::Player*>(mActor)->_26b0.sub_7100E7C0EC();
            if (auto* controller = mActor->getCharacterController())
                controller->sub_7100F5F6FC(mActor->getVelocity() * 30.0f);
            static_cast<ksys::act::Player*>(mActor)->_c50.set(0x800000000);
            mActor->getASList()->x_2(0x42, 0x1b, false, false);
        }
    }
}

void PlayerLaunch::leave_() {}

void PlayerLaunch::loadParams_() {
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mAddLinearImpulse_s, "AddLinearImpulse");
    getStaticParam(&mAddRollImpulse_s, "AddRollImpulse");
    getStaticParam(&mNoRagdollTime_s, "NoRagdollTime");
    getStaticParam(&mDamage_s, "Damage");
    getDynamicParam(&mBasePos_d, "BasePos");
}

void PlayerLaunch::calc_() {
    if (!static_cast<ksys::act::Player*>(mActor)->stillAlive())
        callPlayerGameOverDemo(mActor);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_1844.value <= sead::Mathf::epsilon()) {
        if (player->getASList()->x(35, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC,
                                   true)) {
            setFinished();
        }
    } else {
        player->_1844.update();
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerLaunch::isChangeable() const {
    return false;
}

}  // namespace uking::action
