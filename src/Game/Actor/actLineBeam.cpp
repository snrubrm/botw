#include <basis/seadNew.h>
#include "Game/Actor/actBeamBase.h"
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
