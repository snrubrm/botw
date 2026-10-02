#include "Game/AI/Action/actionPlayerGrabPut.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerGrabPut::PlayerGrabPut(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabPut::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGrabPut::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    static_cast<ksys::act::Player*>(mActor)->x_19(-1.0f);
}

void PlayerGrabPut::loadParams_() {
    getStaticParam(&mPutStartFrmae_s, "PutStartFrmae");
}

void PlayerGrabPut::calc_() {
    PlayerAction::calc_();
}

bool PlayerGrabPut::isChangeable() const {
    return false;
}

}  // namespace uking::action
