#include "Game/Actor/actGuardian.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGuardian.h"

namespace uking::act {

ksys::act::BaseProc* Guardian::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Guardian(arg);
}

// NON_MATCHING: member types incomplete
Guardian::~Guardian() = default;

bool Guardian::m33() {
    return getParam()->getRes().mGParamList->getGuardian()->mGuardianControllerType.ref() == 2;
}

void Guardian::sub_7100034514(bool on) {
    _14c8.change(4, on);
}

void Guardian::sub_710003B090(u32 value) {
    _14d4 = value;
}

void Guardian::updateMtxFromPhysics() {
    if (auto* body = mMainBody.load()) {
        mMtx = body->getTransform();
        nullsub_4648();
    } else {
        Actor::updateMtxFromPhysics();
    }
}

ksys::phys::NavMeshCharacter* Guardian::m45() {
    if (_15b0)
        return _15b0->_30;
    return Actor::m45();
}

}  // namespace uking::act
