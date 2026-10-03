#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"

namespace ksys::act {

Area::Area(const CreateArg& arg) : AreaActor(arg) {
    phys::receiverMaskEnableLayer(&_890, phys::ContactLayer::SensorPlayer);
}

BaseProc* Area::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Area(arg);
}

void Area::m149(phys::RigidBody* body) {
    AreaActor::m149(body);
    body->setSensorCustomReceiver(_890);
}

void Area::m151() {
    if (_848)
        _848->enableLayer(phys::ContactLayer::SensorPlayer);
    if (_850) {
        _850->subscribeLayerAndMask2(phys::ContactLayer::SensorPlayer);
    }
}

phys::ContactLayer Area::m152() {
    return phys::ContactLayer::SensorCustomReceiver;
}

}  // namespace ksys::act
