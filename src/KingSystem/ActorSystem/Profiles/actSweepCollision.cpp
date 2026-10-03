#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace ksys::act {

SweepCollision::SweepCollision(const CreateArg& arg) : AreaActor(arg) {}

BaseProc* SweepCollision::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) SweepCollision(arg);
}

void SweepCollision::m151() {
    if (_848)
        _848->enableLayer(phys::ContactLayer::EntityPlayer);
    if (_850)
        _850->subscribeLayer(phys::ContactLayer::EntityPlayer);
}

phys::ContactLayer SweepCollision::m152() {
    return phys::ContactLayer::EntityGround;
}

}  // namespace ksys::act
