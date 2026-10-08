#include "Game/Actor/actHorseRideInfo.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actRideable.h"
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

ksys::act::BaseProcLink* sub_7100E811F0(ksys::act::Actor* actor) {
    auto* info = actor->getPlayerRideInfo();
    if (!info)
        return &ksys::act::sUnk_71026505e0;
    return &info->_18;
}

// NON_MATCHING: the original loads the ridden actor's x / z before the actor's own
f32 sub_7100E8134C(ksys::act::Actor* actor, ksys::act::Actor* ride_actor) {
    const auto& ride_mtx = ride_actor->getMtx();
    const auto& mtx = actor->getMtx();
    const f32 ride_angle = sead::Mathf::rad2deg(std::atan2(ride_mtx(0, 2), ride_mtx(2, 2)));
    const f32 angle = sead::Mathf::rad2deg(std::atan2(mtx(0, 3) - ride_mtx(0, 3), mtx(2, 3) - ride_mtx(2, 3)));
    return angle - ride_angle;
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

// Separate TU from Rideable::sub_7100E7EF1C, which this tail-calls: the original keeps it out of line.
void sub_7100E80D18(ksys::act::Actor* actor) {
    if (!actor)
        return;
    auto* rideable = actor->getHorseOptionsMaybe();
    if (rideable && rideable->_c == 1)
        rideable->sub_7100E7EF1C();
}

}  // namespace uking::act
