#include "Game/Actor/actMotorcycle.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

// Accessor-based wrappers in the TU 0x71002c802c-0x71002c8548 (lane4 s44; placeholder names, the CSV has none). They cast
// the accessor's proc to a Motorcycle (the default value without one). Own file: Motorcycle::x_1 is out of line in the
// original.

// inline-only in the original; name is a guess (same helper as in acc::Weapon / acc::Armor).
static ksys::act::BaseProc* getProcIfActor(ksys::act::BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<ksys::act::Actor>(proc))
        return proc;
    return nullptr;
}

static inline uking::act::Motorcycle* getMotorcycle(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = static_cast<ksys::act::Actor*>(getProcIfActor(accessor.getProc()));
    return sead::DynamicCast<uking::act::Motorcycle>(actor);
}

// 0x71002c802c: whether the accessor's actor is a Motorcycle.
bool sub_71002C802C(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = static_cast<ksys::act::Actor*>(getProcIfActor(accessor.getProc()));
    return sead::IsDerivedFrom<uking::act::Motorcycle>(actor);
}

// 0x71002c811c: the centre of mass of the main body.
bool sub_71002C811C(const ksys::act::ActorConstDataAccess& accessor, sead::Vector3f* out) {
    if (auto* motorcycle = getMotorcycle(accessor)) {
        motorcycle->x_1(out);
        return true;
    }
    return false;
}

// 0x71002c8220: the position.
bool sub_71002C8220(const ksys::act::ActorConstDataAccess& accessor, sead::Vector3f* out) {
    if (auto* motorcycle = getMotorcycle(accessor)) {
        motorcycle->getMtx().getTranslation(*out);
        return true;
    }
    return false;
}

// 0x71002c8330: `_1178`, returning bit 2 of `_f88`'s byte 3.
bool sub_71002C8330(const ksys::act::ActorConstDataAccess& accessor, sead::Vector3f* out) {
    if (auto* motorcycle = getMotorcycle(accessor)) {
        *out = motorcycle->_1178;
        return motorcycle->_f88.isOnBit(26);
    }
    return false;
}

// 0x71002c8444: the linear velocity of the main body.
bool sub_71002C8444(const ksys::act::ActorConstDataAccess& accessor, sead::Vector3f* out) {
    if (auto* motorcycle = getMotorcycle(accessor)) {
        motorcycle->_bb8->getLinearVelocity(out);
        return true;
    }
    return false;
}

// 0x71002c8548: bit 2 of `_f88`'s byte 4.
bool sub_71002C8548(const ksys::act::ActorConstDataAccess& accessor) {
    auto* motorcycle = getMotorcycle(accessor);
    return motorcycle ? motorcycle->_f88.isOnBit(34) : false;
}
