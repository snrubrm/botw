#include "Game/AI/aiUnk_7100E81220.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

bool sub_7100E81220(ksys::act::Actor* actor, ksys::act::ActorConstDataAccess* accessor) {
    if (auto* info = actor->getPlayerRideInfo())
        return ksys::act::acquireActor(&info->_18, accessor);
    return false;
}
