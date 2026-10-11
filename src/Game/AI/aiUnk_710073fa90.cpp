#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
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

bool sub_7100740118(sead::Matrix33f* mtx, const sead::Vector3f& target, f32 a, f32 b,
                    f32 c) {
    sead::Vector3f up;
    mtx->getBase(up, 1);
    const bool reached = sub_710002F6D8(&up, target, a, b, c);
    const sead::Vector3f forward = mtx->getBase(2);
    ksys::util::sub_71011EFE58(mtx, forward, up, false);
    return reached;
}

bool sub_710074018C(sead::Matrix33f* mtx, const sead::Vector3f& target, f32 a, f32 b,
                    f32 c) {
    sead::Vector3f forward;
    mtx->getBase(forward, 2);
    const bool reached = sub_710002F6D8(&forward, target, a, b, c);
    const sead::Vector3f up = mtx->getBase(1);
    ksys::util::sub_71011EFFA8(mtx, forward, up, false);
    return reached;
}

bool sub_7100741628(sead::Matrix33f* mtx, const sead::Vector3f& target, f32 a, f32 b,
                    f32 c) {
    sead::Vector3f up;
    mtx->getBase(up, 1);
    const bool reached = sub_710002F6D8(&up, target, a, b, c);
    const sead::Vector3f forward = mtx->getBase(2);
    ksys::util::sub_71011EFE58(mtx, forward, up, true);
    return reached;
}

void sub_7100740DC4(sead::Matrix33f* mtx, const sead::Vector3f& up) {
    const sead::Vector3f forward = mtx->getBase(2);
    ksys::util::sub_71011EFE58(mtx, forward, up, false);
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

bool sub_710073FBC0(sead::Matrix33f* mtx, const sead::Matrix33f& target, f32 a, f32 b,
                    f32 c) {
    f32 angle = 0;
    sead::Vector3f axis = sead::Vector3f::ey;
    ksys::util::sub_71011EF1C4(&axis, &angle, *mtx, target, sead::Vector3f::ey);
    return sub_710073FC58(mtx, target, axis, angle, a, b, c);
}

// NON_MATCHING: local matrix, axis and angle stack placement differs.
bool sub_710073FF90(sead::Matrix33f* mtx, const sead::Matrix34f& target, f32 a, f32 b,
                    f32 c) {
    const sead::Matrix33f rotation(target);
    sead::Vector3f axis = sead::Vector3f::ey;
    f32 angle = 0;
    ksys::util::sub_71011EF1C4(&axis, &angle, *mtx, rotation, sead::Vector3f::ey);
    return sub_710073FC58(mtx, rotation, axis, angle, a, b, c);
}

// NON_MATCHING: boolean branching and local stack placement differ.
bool sub_710074006C(sead::Matrix33f* mtx, const sead::Vector3f& front,
                    const sead::Vector3f& up, bool flag, f32 a, f32 b, f32 c) {
    sead::Matrix33f target;
    if (flag)
        ksys::util::sub_71011EFE58(&target, front, up, false);
    else
        ksys::util::sub_71011EFFA8(&target, front, up, false);
    sead::Vector3f axis = sead::Vector3f::ey;
    f32 angle = 0;
    ksys::util::sub_71011EF1C4(&axis, &angle, *mtx, target, sead::Vector3f::ey);
    return sub_710073FC58(mtx, target, axis, angle, a, b, c);
}

// NON_MATCHING: cross-product temporaries and retained constant address change allocation and scheduling.
bool sub_7100740200(sead::Matrix33f* mtx, const sead::Vector3f& front, f32 a, f32 b,
                    f32 c) {
    const sead::Vector3f right = front.cross(sead::Vector3f::ey);
    const sead::Vector3f up = right.cross(front);
    sead::Matrix33f target;
    ksys::util::sub_71011EFE58(&target, front, up, false);
    sead::Vector3f axis = sead::Vector3f::ey;
    f32 angle = 0;
    ksys::util::sub_71011EF1C4(&axis, &angle, *mtx, target, sead::Vector3f::ey);
    return sub_710073FC58(mtx, target, axis, angle, a, b, c);
}

bool sub_71007404F0(sead::Matrix33f* mtx, const sead::Matrix33f& target, f32 a) {
    sead::Vector3f axis = sead::Vector3f::ey;
    f32 angle = 0;
    ksys::util::sub_71011EF1C4(&axis, &angle, *mtx, target, sead::Vector3f::ey);
    return sub_7100740570(mtx, target, axis, angle, a);
}

// NON_MATCHING: boolean branching and local stack placement differ.
bool sub_71007407F0(sead::Matrix33f* mtx, const sead::Vector3f& front,
                    const sead::Vector3f& up, bool flag, f32 a) {
    sead::Matrix33f target;
    if (flag)
        ksys::util::sub_71011EFE58(&target, front, up, false);
    else
        ksys::util::sub_71011EFFA8(&target, front, up, false);
    sead::Vector3f axis = sead::Vector3f::ey;
    f32 angle = 0;
    ksys::util::sub_71011EF1C4(&axis, &angle, *mtx, target, sead::Vector3f::ey);
    return sub_7100740570(mtx, target, axis, angle, a);
}

// NON_MATCHING: boolean branching and saved argument allocation differ.
bool sub_7100740D50(sead::Matrix33f* mtx, const sead::Vector3f& front,
                    const sead::Vector3f& up, const sead::Vector3f& axis, bool flag,
                    bool use_front, f32 a) {
    sead::Matrix33f target;
    if (use_front)
        ksys::util::sub_71011EFE58(&target, front, up, false);
    else
        ksys::util::sub_71011EFFA8(&target, front, up, false);
    return sub_7100740C10(mtx, target, axis, flag, a);
}

// NON_MATCHING: local matrix, axis and angle stack placement differs.
bool sub_710074149C(sead::Matrix33f* mtx, const sead::Matrix34f& target, f32 a, f32 b,
                    f32 c) {
    const sead::Matrix33f rotation(target);
    sead::Vector3f axis = sead::Vector3f::ey;
    f32 angle = 0;
    ksys::util::sub_71011EF1C4(&axis, &angle, *mtx, rotation, sead::Vector3f::ey);
    return sub_7100741164(mtx, rotation, axis, angle, a, b, c);
}

// NON_MATCHING: boolean branching and local stack placement differ.
bool sub_7100741578(sead::Matrix33f* mtx, const sead::Vector3f& front,
                    const sead::Vector3f& up, bool flag, f32 a, f32 b, f32 c) {
    sead::Matrix33f target;
    if (flag)
        ksys::util::sub_71011EFE58(&target, front, up, true);
    else
        ksys::util::sub_71011EFFA8(&target, front, up, true);
    sead::Vector3f axis = sead::Vector3f::ey;
    f32 angle = 0;
    ksys::util::sub_71011EF1C4(&axis, &angle, *mtx, target, sead::Vector3f::ey);
    return sub_7100741164(mtx, target, axis, angle, a, b, c);
}

// NON_MATCHING: boolean branching and local stack placement differ.
bool sub_710074191C(sead::Matrix33f* mtx, const sead::Vector3f& front,
                    const sead::Vector3f& up, bool flag, f32 a) {
    sead::Matrix33f target;
    if (flag)
        ksys::util::sub_71011EFE58(&target, front, up, true);
    else
        ksys::util::sub_71011EFFA8(&target, front, up, true);
    sead::Vector3f axis = sead::Vector3f::ey;
    f32 angle = 0;
    ksys::util::sub_71011EF1C4(&axis, &angle, *mtx, target, sead::Vector3f::ey);
    return sub_710074169C(mtx, target, axis, angle, a);
}
