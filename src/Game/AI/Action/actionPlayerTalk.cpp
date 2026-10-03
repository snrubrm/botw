#include "Game/AI/Action/actionPlayerTalk.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerTalk::PlayerTalk(const InitArg& arg) : PlayerAction(arg) {}

PlayerTalk::~PlayerTalk() = default;

bool PlayerTalk::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerTalk::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerTalk::leave_() {
    if (!static_cast<ksys::act::Player*>(mActor)->isRidingHorse())
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    if (static_cast<ksys::act::Player*>(mActor)->isRidingHorse())
        static_cast<ksys::act::Player*>(mActor)->nullsub_2601();
}

void PlayerTalk::loadParams_() {
    getDynamicParam(&mGreetingType_d, "GreetingType");
}

void PlayerTalk::calc_() {
    PlayerAction::calc_();
}

bool PlayerTalk::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
