#include "Game/Actor/aiUnk_7102450d10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

Unk_7102450d10::Unk_7102450d10(ksys::act::Actor* actor) : mActor(actor) {
    _30 = 0;
    _8.fill(0);
}

Unk_7102450d10::~Unk_7102450d10() = default;

// NON_MATCHING: the unrolled body has a different shared return branch.
bool Unk_7102450d10::sub_7100714454() {
    auto* controller = mActor->getCharacterController();
    const int body_index = controller ? controller->_224 : 0;
    for (int i = 0; i < 10; ++i) {
        if (_8[i] == body_index)
            return (i & 1) != 0;
    }
    return false;
}

void Unk_7102450d10::sub_7100714B88() {
    if (auto* controller = mActor->getCharacterController()) {
        if (_30 >= 0)
            controller->sub_7100F5F270(_30);
    }
    if (auto* body = mActor->findPhysicsBodyByName(ksys::act::getStr_Tgt().cstr(), "TgtFlyBody"))
        body->setContactLayer(ksys::phys::ContactLayer::SensorEnemy);
    if (auto* body = ksys::act::sub_7100EE5DD0(mActor, "TgtFlyBody"))
        body->setContactLayer(ksys::phys::ContactLayer::SensorChemical);
    ksys::act::disableAttClient(mActor, "AutoAimHidden");
    ksys::act::enableAttClient(mActor, "AutoAim");
    ksys::act::enableAttClient(mActor, "LockOn");
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F60604();
        controller->sub_7100F5E714(false);
    }
}
