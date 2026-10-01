#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::act {

Unk_710072AFD0::Unk_710072AFD0() = default;

Unk_710072AFD0::~Unk_710072AFD0() = default;

bool Unk_710072AFD0::sub_710072AFFC(Actor* actor) {
    if (changeMotionType(sub_710072ACF8(actor), MotionType::Hover)) {
        _c = 1;
        return true;
    }

    auto* body = actor->getMainBody();
    if (!body) {
        _c = 0;
        return false;
    }

    _8 = body->getGravityFactor();
    body->setGravityFactor(0.0f);
    _c = 2;
    return true;
}

void Unk_710072AFD0::sub_710072B078(Actor* actor) {
    switch (_c) {
    case 1:
        resetMotionType(sub_710072ACF8(actor));
        break;
    case 2:
        if (auto* body = actor->getMainBody()) {
            body->setGravityFactor(_8);
            body->setMotionFlag(phys::RigidBody::MotionFlag::_20000);
        }
        break;
    }
    _c = 0;
}

}  // namespace ksys::act
