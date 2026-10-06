#include <basis/seadNew.h>
#include <prim/seadScopedLock.h>
#include "Game/Actor/actBeamBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleRigidBody.h"

namespace uking::act {

LineBeam::LineBeam(const CreateArg& arg) : BeamBase(arg) {}

ksys::act::BaseProc* LineBeam::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) LineBeam(arg);
}

void LineBeam::m63() {
    DynamicActor::m63();
    _d40 = -1;
    _d48.reset();
}

void LineBeam::initMaybe() {
    BeamBase::initMaybe();
    if (auto* body = findPhysicsBodyByName(sub_71007A24BC()->cstr(), "Beam"))
        _d28 = sead::DynamicCast<ksys::phys::CapsuleRigidBody>(body);
}

void LineBeam::m165(sead::Vector3f* out) {
    out->set(_d1c);
}

void LineBeam::m166() {
    _d10 = 0;
}

}  // namespace uking::act

// Accessor-based wrapper in the LineBeam TU (0x71002c7d1c; lane4 s44; placeholder name, the CSV has none): sets `_cc8`
// (under the lock `_c88`) of the accessor's actor if it is a LineBeam.
// inline-only in the original; name is a guess (same helper as in acc::Weapon / acc::Armor).
static ksys::act::BaseProc* getProcIfActor(ksys::act::BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<ksys::act::Actor>(proc))
        return proc;
    return nullptr;
}

void sub_71002C7D1C(const ksys::act::ActorConstDataAccess& accessor, const sead::Vector3f& value) {
    auto* actor = static_cast<ksys::act::Actor*>(getProcIfActor(accessor.getProc()));
    if (auto* beam = sead::DynamicCast<uking::act::LineBeam>(actor)) {
        auto lock = sead::makeScopedLock(beam->_c88);
        beam->_cc8 = value;
    }
}
