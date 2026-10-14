#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::act {

Unk_71023cee88::~Unk_71023cee88() = default;

bool Unk_71023cee88::m5(const ksys::act::ActorLinkConstDataAccess& accessor) {
    if (auto* rideable = accessor.getHorseOptions())
        return rideable->m22(Unk_7100e8b2b8::Unk8::_3);
    return false;
}

}  // namespace uking::act
