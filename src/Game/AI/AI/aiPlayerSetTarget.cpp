#include "Game/AI/AI/aiPlayerSetTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

PlayerSetTarget::PlayerSetTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerSetTarget::~PlayerSetTarget() = default;

bool PlayerSetTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerSetTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    sub_71005D8DE8(mActor, ksys::act::PlayerInfo::getSomeProcLink(), &player.getActorMtx(),
                   &player.getPreviousPos());
    changeChild("行動", params);
}

void PlayerSetTarget::calc_() {}

void PlayerSetTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerSetTarget::loadParams_() {}

}  // namespace uking::ai
