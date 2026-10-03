#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/physMaterialMask.h"

namespace ksys::act {

AreaActor::AreaActor(const CreateArg& arg) : Actor(arg) {}

void AreaActor::preDelete2_(const PreDeleteArg& arg) {
    _878 = nullptr;
    if (_840) {
        if (_840->isAddedToWorld())
            _840->x_10();
        if (_840) {
            delete _840;
            _840 = nullptr;
        }
    }
    if (_848) {
        phys::CollisionInfo::free(_848);
        _848 = nullptr;
    }
    if (_850) {
        phys::ContactPointInfo::free(_850);
        _850 = nullptr;
    }
}

void AreaActor::m149(phys::RigidBody* body) {
    body->setCollisionInfo(_848);
    body->setContactPointInfo(_850);
    body->updateCollidableQualityType(true);
}

void AreaActor::m150() {
    phys::MaterialMask mask(0u);
    if (!(_878 == nullptr))
        (this->*_878)(&mask);
}

phys::ContactLayer AreaActor::m152() {
    return phys::ContactLayer(phys::ContactLayer::size());
}

void AreaActor::sub_7100E2677C() {
    _88a = 0;
}

}  // namespace ksys::act
