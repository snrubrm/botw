#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::act {

HorseRideInfo::~HorseRideInfo() = default;

bool HorseRideInfo::sub_7100E7BEC0(ksys::act::BaseProc* proc) {
    if (!proc)
        return false;

    ksys::act::ActorConstDataAccess accessor(proc);
    if (!sub_7100E7BF5C(accessor, _18.hasProcById(proc)))
        return false;
    _18.acquire(proc, false);
    return true;
}

bool HorseRideInfo::sub_7100E7C054(ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(link, &accessor))
        return false;
    if (!sub_7100E7BF5C(accessor, _18 == *link))
        return false;
    _18 = *link;
    return true;
}

bool HorseRideInfo::init() {
    m7();
    _30 = 0;
    _18.reset();
    return true;
}

void HorseRideInfo::sub_7100E7C350() {
    m8();
    _30 = 0;
    _18.reset();
}

}  // namespace uking::act
