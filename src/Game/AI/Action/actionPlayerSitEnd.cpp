#include "Game/AI/Action/actionPlayerSitEnd.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerSitEnd::PlayerSitEnd(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSitEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SitDownEd", true, -1.0f);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5EEB8(0.0f);
}

void PlayerSitEnd::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5EEB8(1.0f);
}

void PlayerSitEnd::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_7100877F00(sead::Vector3f::zero);
    if (mActor->getASList()->x_4(0, 0))
        setFinished();
}

bool PlayerSitEnd::isChangeable() const {
    return false;
}

}  // namespace uking::action
