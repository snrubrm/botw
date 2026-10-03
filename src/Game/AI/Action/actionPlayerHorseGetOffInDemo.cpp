#include "Game/AI/Action/actionPlayerHorseGetOffInDemo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerHorseGetOffInDemo::PlayerHorseGetOffInDemo(const InitArg& arg) : PlayerAction(arg) {}

void PlayerHorseGetOffInDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    if (auto* ride_info = mActor->getPlayerRideInfo()) {
        ride_info->sub_7100E7C0EC();
        if (auto* cc = mActor->getCharacterController())
            cc->sub_7100F5EC30();
    }
    mActor->sub_71011DA834(mActor->getModelBindInfo());
}

void PlayerHorseGetOffInDemo::leave_() {}

void PlayerHorseGetOffInDemo::calc_() {
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    setFinished();
}

bool PlayerHorseGetOffInDemo::isChangeable() const {
    return false;
}

}  // namespace uking::action
