#include "Game/AI/Action/actionPlayerSitStart.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

PlayerSitStart::PlayerSitStart(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSitStart::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSitStart::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5EEB8(1.0f);
}

void PlayerSitStart::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_7100877F00(sead::Vector3f::zero);
    if (mActor->getASList()->x_4(0, 0))
        setFinished();
}

bool PlayerSitStart::isChangeable() const {
    return false;
}

}  // namespace uking::action
