#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::act {

Unk_71023cee88::~Unk_71023cee88() = default;

bool Unk_71023cee88::m5(const ksys::act::ActorConstDataAccess& accessor) {
    if (auto* rideable = accessor.getHorseOptions())
        return rideable->m22(3);
    return false;
}

}  // namespace uking::act
