#include "Game/AI/Action/actionReserveParashawlStart.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::action {

ReserveParashawlStart::ReserveParashawlStart(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ReserveParashawlStart::~ReserveParashawlStart() = default;

bool ReserveParashawlStart::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ReserveParashawlStart::loadParams_() {}

bool ReserveParashawlStart::oneShot_() {
    bool reserved;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        reserved = player.reserveParashawlStart();
    }
    return !reserved;
}

}  // namespace uking::action
