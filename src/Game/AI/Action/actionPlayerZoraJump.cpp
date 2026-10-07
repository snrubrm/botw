#include "Game/AI/Action/actionPlayerZoraJump.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

PlayerZoraJump::PlayerZoraJump(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: vector scaling order and stack placement differ.
void PlayerZoraJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(2);
    static_cast<ksys::act::Player*>(mActor)->_c48.set(0x1000000);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Jump", true, -1.0f);
    if (auto* controller = mActor->getCharacterController()) {
        const f32 height = *mJumpHeight_s;
        sead::Vector3f target = *mTargetPos_d;
        target.y += *mJumpHeight_s;
        sead::Vector3f velocity = sead::Vector3f::zero;
        controller->sub_7100F62640(height, &velocity);
        auto* player = static_cast<ksys::act::Player*>(mActor);
        sead::Vector3f gravity;
        sub_710072DC50(&gravity, player);
        gravity *= 1.0f / 900.0f;
        f32 speed;
        f32 time;
        sub_710072CF4C(velocity.y / 30.0f, &speed, &time, &player->_1770, &target, &gravity);
        if (speed > *mJumpSpeedF_s)
            speed = *mJumpSpeedF_s;
        static_cast<ksys::act::Player*>(mActor)->_20bc.value = speed;
        static_cast<ksys::act::Player*>(mActor)->_20bc.prev_value = speed;
        static_cast<ksys::act::Player*>(mActor)->_1c68 = ksys::util::Unk_7101EC6BAC(
            sead::Mathf::atan2Idx(target.x - static_cast<ksys::act::Player*>(mActor)->_1770.x,
                                 target.z - static_cast<ksys::act::Player*>(mActor)->_1770.z));
        static_cast<ksys::act::Player*>(mActor)->x_53(
            static_cast<ksys::act::Player*>(mActor)->_1c68);
        controller->sub_7100F5EF08(true);
        controller->sub_7100F62B70(height);
    }
}

void PlayerZoraJump::leave_() {}

void PlayerZoraJump::loadParams_() {
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void PlayerZoraJump::calc_() {
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (mActor->getVelocity().y <= 0.01f)
        setFinished();
}

bool PlayerZoraJump::isChangeable() const {
    return true;
}

}  // namespace uking::action
