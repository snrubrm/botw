#include "Game/AI/Action/actionPlayerHellNoFade.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerHellNoFade::PlayerHellNoFade(const InitArg& arg) : PlayerAction(arg) {}

void PlayerHellNoFade::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHellNoFade::leave_() {
    auto* actor = mActor;
    actor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    static_cast<ksys::act::Player*>(mActor)->_c48.reset(0x80000);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EEB8(1.0f);
        controller->sub_7100F63388(false, -1);
        controller->sub_7100F5F458(ksys::act::MotionType::_0);
    }
}

void PlayerHellNoFade::loadParams_() {
    getStaticParam(&mCleaningTime_s, "CleaningTime");
}

void PlayerHellNoFade::calc_() {
    PlayerAction::calc_();
}

bool PlayerHellNoFade::isChangeable() const {
    return false;
}

}  // namespace uking::action
