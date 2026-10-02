#include "Game/AI/Action/actionAreaActorObserveByGroup.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

AreaActorObserveByGroup::AreaActorObserveByGroup(const InitArg& arg) : AreaActorObserve(arg) {}

AreaActorObserveByGroup::~AreaActorObserveByGroup() = default;

bool AreaActorObserveByGroup::init_(sead::Heap* heap) {
    mFilters[0].bind(this, &AreaActorObserveByGroup::sub_710009E7AC);
    mFilters[1].bind(this, &AreaActorObserveByGroup::sub_710009E7C0);
    mFilters[2].bind(this, &AreaActorObserveByGroup::sub_710009E7C8);
    mFilters[3].bind(this, &AreaActorObserveByGroup::sub_710009E7D0);
    mFilters[4].bind(this, &AreaActorObserveByGroup::sub_710009E848);
    mGroup = *mActorGroupForObserveTag_m;
    return AreaActorObserve::init_(heap);
}

void AreaActorObserveByGroup::m9() {
    if (*mActorGroupForObserveTag_m != mGroup)
        mGroup = *mActorGroupForObserveTag_m;
}

bool AreaActorObserveByGroup::sub_710009E7AC(const ksys::act::ActorConstDataAccess& accessor) {
    return accessor.hasTag(ksys::act::tags::Arrow);
}

bool AreaActorObserveByGroup::sub_710009E7C0(const ksys::act::ActorConstDataAccess& accessor) {
    return accessor.isWeaponProfile();
}

bool AreaActorObserveByGroup::sub_710009E7C8(const ksys::act::ActorConstDataAccess& accessor) {
    return accessor.sub_7100D0FEAC();
}

bool AreaActorObserveByGroup::sub_710009E7D0(const ksys::act::ActorConstDataAccess& accessor) {
    auto* rideable = accessor.getHorseOptions();
    if (!rideable)
        return false;

    auto* base = static_cast<act::Unk_7100e8b2b8*>(rideable);
    switch (base->sub_7100E8C03C()) {
    case 1:
    case 3:
    case 4:
    case 6:
        if (base->_c == 1)
            return !base->sub_7100E8BFF4();
        return false;
    default:
        return false;
    }
}

void AreaActorObserveByGroup::m32() {
    getMapUnitParam(&mActorGroupForObserveTag_m, "ActorGroupForObserveTag");
}

bool AreaActorObserveByGroup::m37(const ksys::act::ActorConstDataAccess& accessor) {
    if (u32(mGroup) > 4)
        return false;
    return mFilters[mGroup](accessor);
}

bool AreaActorObserveByGroup::m16(ksys::phys::RigidBody* body) {
    if (body && mGroup == 4) {
        const auto name = body->getHkBodyName();
        if (name != "SensorForArea")
            return true;
    }
    return ActorObserver::m16(body);
}

}  // namespace uking::action
