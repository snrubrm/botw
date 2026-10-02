#include "Game/AI/Action/actionDemoFindPlayer.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

DemoFindPlayer::DemoFindPlayer(const InitArg& arg) : TimeredASPlay(arg) {}

DemoFindPlayer::~DemoFindPlayer() = default;

void DemoFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredASPlay::enter_(params);
    sub_71005D8DE8(mActor, ksys::act::PlayerInfo::getSomeProcLink(), nullptr, nullptr);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
}

void DemoFindPlayer::loadParams_() {
    TimeredASPlay::loadParams_();
}

}  // namespace uking::action
