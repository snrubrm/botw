#include "Game/AI/aiUnk_7102450058.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

Unk_7102450298::Unk_7102450298(ksys::act::Actor* actor) : CarriedData(actor) {}

bool Unk_7102450298::sub_71006F8AB4() const {
    if (!_30)
        return true;
    return !(_30->_50 & 1);
}

void Unk_7102450298::x_10() {
    if (_30)
        _30->sub_7100F6A074();
}

bool Unk_7102450298::x_15() {
    return _30 && (_30->_50 & 1);
}

void Unk_7102450298::x_18(ksys::act::Actor* actor) {
    if (!actor || !mActor || !_30)
        return;
    auto* body = sub_71007394DC(mActor);
    auto* other_body = sub_71007394DC(actor);
    if (!body || !other_body)
        return;
    _30->sub_7100F6AAA4(body, other_body);
    auto* constraint = _30;
    constraint->sub_7100F6D420(body->getTransform(), other_body->getTransform(), body->getTransform());
    _30->sub_7100F69FF0();
}

void Unk_7102450298::x_22(ksys::phys::RigidBody* body) {
    if (!body)
        return;
    const sead::Matrix34f& mtx = mActor->getMtx();
    _30->sub_7100F6D420(mtx, body->getTransform(), mtx);
}

// NON_MATCHING: the original loads all three components into registers and copies the vector onto itself before
// normalising (the vector is a copy of the out parameter); ours normalises in place from memory
void Unk_7102450298::x_20() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    sead::Vector3f velocity;
    controller->sub_7100F5F598(&velocity);
    const sead::Vector2f horizontal(velocity.x, velocity.z);
    velocity.normalize();
    sub_710072C1B4(controller, velocity);
    controller->sub_7100F5E7F0(horizontal.length());
    controller->sub_7100F5FC8C(mActor->getMtx());
}
