#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

// The forwarding wrappers are kept apart from the functions they call (in aiUnk_710073fa94.cpp), as in the
// original, where they are not inlined.

void sub_710073FA90(sead::Matrix33f* mtx, ksys::act::Actor* actor) {
    sub_710073FA94(mtx, actor);
}

void sub_7100741034(sead::Matrix33f* mtx, ksys::act::Actor* actor) {
    sub_7100741038(mtx, actor);
}

void sub_71007419B4(sead::Matrix33f* mtx, const sead::Vector3f& up) {
    const sead::Vector3f z{mtx->m[0][2], mtx->m[1][2], mtx->m[2][2]};
    ksys::util::sub_71011EFE58(mtx, z, up, true);
}

void sub_7100740E04(const sead::Matrix33f& mtx, ksys::phys::CharacterController* controller) {
    const sead::Matrix34f transform(mtx);
    controller->sub_7100F5FC8C(transform);
}

void sub_7100740E8C(const sead::Matrix33f& mtx, ksys::phys::RigidBody* body) {
    const sead::Matrix34f transform(mtx);
    body->changeRotation(transform);
}

void sub_71007419F4(const sead::Matrix33f& mtx, ksys::phys::CharacterController* controller) {
    const sead::Matrix34f transform(mtx);
    controller->sub_7100F5FC8C(transform);
}

void sub_7100741A7C(const sead::Matrix33f& mtx, ksys::phys::RigidBody* body) {
    const sead::Matrix34f transform(mtx);
    body->changeRotation(transform);
}
