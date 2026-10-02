#include "Game/AI/Action/actionPlayerCutAfterJust.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerCutAfterJust::PlayerCutAfterJust(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutAfterJust::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

// NON_MATCHING: the original copies the velocity once more (element-wise self-copy after the call)
void PlayerCutAfterJust::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f vel;
        controller->sub_7100F5F598(&vel);
        if (vel.y > 0.0f) {
            vel.y = 0.0f;
            controller->sub_7100F5F6FC(vel);
        }
    }
    auto* player = static_cast<ksys::act::Player*>(mActor);
    sub_71005D79AC(player, player->playerWeapons_return0(), act::Unk_71002edaec(1));
    static_cast<ksys::act::Player*>(mActor)->_1d70 = ksys::Timer(0.0f, 0.0f);
}

void PlayerCutAfterJust::loadParams_() {
    getStaticParam(&mSlowContTime_s, "SlowContTime");
    getStaticParam(&mLastCutAcceptTime_s, "LastCutAcceptTime");
    getStaticParam(&mLastCutAcceptTimeLSword_s, "LastCutAcceptTimeLSword");
    getStaticParam(&mLastCutAcceptTimeSpear_s, "LastCutAcceptTimeSpear");
    getStaticParam(&mForceSlowTime_s, "ForceSlowTime");
}

void PlayerCutAfterJust::calc_() {
    PlayerAction::calc_();
}

bool PlayerCutAfterJust::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
