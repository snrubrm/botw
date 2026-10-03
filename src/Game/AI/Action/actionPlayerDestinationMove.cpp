#include "Game/AI/Action/actionPlayerDestinationMove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerDestinationMove::PlayerDestinationMove(const InitArg& arg) : PlayerGuidedMove(arg) {}

void PlayerDestinationMove::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 x = *mDestPosX_d;
    const f32 y = *mDestPosY_d;
    const f32 z = *mDestPosZ_d;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    _4c.set(x - player->_1770.x, y - player->_1770.y, z - player->_1770.z);
    PlayerGuidedMove::enter_(params);
}

void PlayerDestinationMove::leave_() {
    PlayerGuidedMove::leave_();
}

void PlayerDestinationMove::loadParams_() {
    PlayerGuidedMove::loadParams_();
    getDynamicParam(&mDestPosX_d, "DestPosX");
    getDynamicParam(&mDestPosY_d, "DestPosY");
    getDynamicParam(&mDestPosZ_d, "DestPosZ");
}

void PlayerDestinationMove::calc_() {
    PlayerGuidedMove::calc_();
}

bool PlayerDestinationMove::isChangeable() const {
    return false;
}

bool PlayerDestinationMove::m33(sead::Vector3f* pos) {
    pos->set(*mDestPosX_d, *mDestPosY_d, *mDestPosZ_d);
    return true;
}

}  // namespace uking::action
