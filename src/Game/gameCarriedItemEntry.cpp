#include "Game/gameActorContextStuff.h"

#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

// NON_MATCHING: scalar initializer stores are scheduled/coalesced differently.
Unk_710243be90::Unk_710243be90() = default;

Unk_710243be90::~Unk_710243be90() {
    if (_50) {
        if (_48)
            _48->setContactPointInfo(nullptr);
        ksys::phys::ContactPointInfo::free(_50);
        _50 = nullptr;
    }
    if (_40) {
        delete _40;
        _40 = nullptr;
    }
    if (_48) {
        delete _48;
        _48 = nullptr;
    }
}

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

bool Unk_710243be90::sub_71006606E8() {
    _40->erase();
    return _48 && _48->removeFromWorldAndResetLinks() && !_30.hasProc();
}

void Unk_710243be90::sub_710066136C() {
    _48->setGravityFactor(0.0f);
    _48->setContactAll();
    _48->removeFromWorld();
    _28 |= 4;
}

void Unk_710243be90::sub_71006613B0(bool delete_actor) {
    if (_28 & 1)
        return;
    _48->removeFromWorld();
    _40->erase();
    if (delete_actor) {
        _28 |= 0x80;
        _48->removeFromWorld();
        _40->erase();
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_30, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        _28 |= 0x81;
    }
    _28 |= 1;
}

void Unk_710243be90::sub_7100661494(bool immediately) {
    _48->removeFromWorld();
    _40->erase();
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_30, &accessor)) {
        if (immediately)
            accessor.deleteEx(ksys::act::BaseProc::DeleteReason::_0);
        else
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    _28 |= 0x81;
}

bool Unk_710243be90::sub_7100661540(const ksys::act::BaseProcLink& link) const {
    return _30 == link;
}

bool Unk_710243be90::sub_7100661650(ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::ActorConstDataAccess other;
    return ksys::act::acquireActor(&_30, &accessor) && ksys::act::acquireActor(link, &other) &&
           accessor.getName() == other.getName();
}

bool Unk_710243be90::sub_710066178C(sead::BufferedSafeString* out) {
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(&_30, &accessor))
        return false;
    out->copy(accessor.getName());
    return true;
}

void Unk_710243be90::sub_71006620CC(sead::Vector3f* position, sead::Quatf* rotation) const {
    if ((_118->_68 & 1) && _58)
        _58->getPositionAndRotation(position, rotation);
    else if (_48)
        _48->getPositionAndRotation(position, rotation);
}

void Unk_710243be90::sub_71006620F8(sead::Matrix34f* matrix) const {
    if ((_118->_68 & 1) && _58)
        _58->getTransform(matrix);
    else if (_48)
        _48->getTransform(matrix);
}
