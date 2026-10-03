#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::act {

HorseRideInfo::~HorseRideInfo() = default;

ksys::act::Actor* getRideActor(ksys::act::Actor* actor) {
    auto* info = actor->getPlayerRideInfo();
    if (!info)
        return nullptr;
    return sead::DynamicCast<ksys::act::Actor>(info->_18.getProc(nullptr, info->mActor));
}

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

void HorseRideInfo::sub_7100E7C4F8(ksys::act::Unk117* arg) {
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(_18.getProc(nullptr, nullptr)))
        actor->x_17(arg);
}

}  // namespace uking::act
