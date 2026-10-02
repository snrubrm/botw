#include "Game/AI/Action/actionEventSendCatchWeaponMsgToPlayer.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

EventSendCatchWeaponMsgToPlayer::EventSendCatchWeaponMsgToPlayer(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSendCatchWeaponMsgToPlayer::~EventSendCatchWeaponMsgToPlayer() = default;

bool EventSendCatchWeaponMsgToPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSendCatchWeaponMsgToPlayer::loadParams_() {}

bool EventSendCatchWeaponMsgToPlayer::oneShot_() {
    auto* actor = mActor;
    if (ksys::act::isWeaponProfile(actor)) {
        if (auto* player = ksys::act::PlayerInfo::instance()->getPlayer()) {
            _20._18.sub_710070E1F8(actor);
            _20.sub_710070DC38(player, true);
        }
    }
    return true;
}

}  // namespace uking::action
