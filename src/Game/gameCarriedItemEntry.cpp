#include "Game/gameActorContextStuff.h"

#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

void Unk_710243be90::sub_7100661988() {
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_30, &accessor) && accessor.isStateCalc())
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

void Unk_710243be90::sub_71006619DC() {
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_30, &accessor) && accessor.isStateSleep())
        accessor.setProperties(0, accessor.getActorMtx(), nullptr, nullptr, nullptr, false, 3, -1);
}

void Unk_710243be90::sub_71006618AC() {
    _48->setGravityFactor(0.0f);
    _48->setContactAll();
    _48->removeFromWorld();
    _48->setLinearVelocity(sead::Vector3f::zero);
    _48->setAngularVelocity(sead::Vector3f::zero);
    _70 = sead::GlobalRandom::instance()->getF32Range(10.0f, 30.0f);
    _74 = sead::GlobalRandom::instance()->getF32Range(50.0f, 70.0f);
}

bool Unk_710243be90::sub_7100661538(ksys::act::BaseProc* proc) const {
    return _30.hasProcById(proc);
}
