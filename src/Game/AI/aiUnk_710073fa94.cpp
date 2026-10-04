#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

// Group A

void sub_710073FA94(sead::Matrix33f* mtx, ksys::act::Actor* actor) {
    if (auto* controller = actor->getCharacterController()) {
        sead::Matrix34f transform;
        controller->sub_7100F626E8(&transform);
        sub_710073FB74(mtx, transform);
    } else if (auto* body = actor->getMainBody()) {
        const sead::Matrix34f transform = body->getTransform();
        sub_710073FB74(mtx, transform);
    } else {
        sub_710073FB74(mtx, actor->getMtx());
    }
}

void sub_710073FB74(sead::Matrix33f* mtx, const sead::Matrix34f& transform) {
    mtx->m[0][0] = transform.m[0][0];
    mtx->m[0][1] = transform.m[0][1];
    mtx->m[0][2] = transform.m[0][2];
    mtx->m[1][0] = transform.m[1][0];
    mtx->m[1][1] = transform.m[1][1];
    mtx->m[1][2] = transform.m[1][2];
    mtx->m[2][0] = transform.m[2][0];
    mtx->m[2][1] = transform.m[2][1];
    mtx->m[2][2] = transform.m[2][2];
}

// Group B (the same code at another address)

void sub_7100741038(sead::Matrix33f* mtx, ksys::act::Actor* actor) {
    if (auto* controller = actor->getCharacterController()) {
        sead::Matrix34f transform;
        controller->sub_7100F626E8(&transform);
        sub_7100741118(mtx, transform);
    } else if (auto* body = actor->getMainBody()) {
        const sead::Matrix34f transform = body->getTransform();
        sub_7100741118(mtx, transform);
    } else {
        sub_7100741118(mtx, actor->getMtx());
    }
}

void sub_7100741118(sead::Matrix33f* mtx, const sead::Matrix34f& transform) {
    mtx->m[0][0] = transform.m[0][0];
    mtx->m[0][1] = transform.m[0][1];
    mtx->m[0][2] = transform.m[0][2];
    mtx->m[1][0] = transform.m[1][0];
    mtx->m[1][1] = transform.m[1][1];
    mtx->m[1][2] = transform.m[1][2];
    mtx->m[2][0] = transform.m[2][0];
    mtx->m[2][1] = transform.m[2][1];
    mtx->m[2][2] = transform.m[2][2];
}
