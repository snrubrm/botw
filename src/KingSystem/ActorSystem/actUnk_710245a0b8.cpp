#include "KingSystem/ActorSystem/actUnk_7102459df8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actUnk_71024ef4e8.h"
#include "KingSystem/ActorSystem/actUnk_71024ef620.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physSystem.h"
#include <math/seadMathCalcCommon.h>

namespace ksys::act {

// NON_MATCHING: contact-point loads and the record index are scheduled differently.
void Unk_710245a0b8::m2(Actor* actor) {
    auto* body = actor->getMainBody();
    if (!body)
        return;
    auto* contacts = body->getContactPointInfo();
    auto it = contacts->begin();
    const auto end = contacts->end();
    for (; it != end; ++it) {
        if (!sub_710079F598(it.getPoint()->body_b))
            continue;
        sead::Vector3f normal = -it.getPoint()->separating_normal;
        if (phys::System::instance())
            phys::System::instance()->getField48().length();
        auto* tag = sead::DynamicCast<PhysicsUserTag>(it.getPoint()->body_b->getUserTag());
        ActorLinkConstDataAccess accessor;
        if (tag)
            tag->acquireActor(&accessor);
        if (sead::Mathf::abs(sead::Mathf::acos(sead::Mathf::clamp(normal.y, -1.0f, 1.0f))) >=
            sead::Mathf::deg2rad(70.0f)) {
            mEntries[mNum].sub_710079F508(
                it.getPointPosition(phys::ContactPointInfo::Iterator::Point::BodyA), normal,
                &accessor, it.getPoint()->material_mask_b, it.getPoint()->material_mask_a);
            if (mNum++ >= 7)
                break;
        }
    }
}

// NON_MATCHING: register allocation of the record pointer for the setter call.
void Unk_710245a0e0::m2(Actor* actor) {
    auto* controller = actor->getCharacterController();
    if (!controller || !controller->sub_7100F5F128())
        return;
    ++mNum;
    sead::Vector3f position;
    controller->sub_7100F5F234(&position);
    const phys::MaterialMask material2(18u);
    const phys::MaterialMask material1(2u);
    mEntries[0].sub_710079F508(controller->sub_7100F5F134(), controller->sub_7100F5F140(),
                             nullptr, material1, material2);
}

// NON_MATCHING: stack slot assignment; the original copies the second vector onto itself before the call.
void Unk_710245a000::m2(Actor* actor) {
    auto* controller = actor->getCharacterController();
    if (!controller || !controller->sub_7100F5F14C())
        return;
    ++mNum;
    sead::Vector3f position;
    controller->sub_7100F5F234(&position);
    const phys::MaterialMask material2(18u);
    const phys::MaterialMask material1(1u);
    sead::Vector3f normal;
    controller->sub_7100F5F6E0(&normal);
    mEntries[0].sub_710079F508(normal, position, nullptr, material1, material2);
}

// NON_MATCHING: the original computes the position address before the counter update; stack slots.
void Unk_710245a028::m2(Actor* actor) {
    auto* player = sead::DynamicCast<uking::act::PlayerBase>(actor);
    if (!player)
        return;

    if (player->_cec.isOnBit(19)) {
        if (player->getAttachedTargetActor2()->_16c)
            ++mNum;
        return;
    }
    if (player->_cec.isOnBit(17)) {
        auto* unk = player->getAttachedTargetActor2()->_c0;
        if (unk && unk->_60.isOnBit(1))
            ++mNum;
        return;
    }
    if (!player->sub_710084CD90() || player->m194()) {
        Unk_710245a000::m2(actor);
        return;
    }

    auto* controller = actor->getCharacterController();
    if (!controller)
        return;
    auto* unk3 = player->getAttachedTargetActor2()->_b8;
    if (!unk3 || !(unk3->_74 & 2))
        return;
    ++mNum;
    const phys::MaterialMask material2(18u);
    const phys::MaterialMask material1(1u);
    sead::Vector3f normal;
    controller->sub_7100F5F6E0(&normal);
    mEntries[0].sub_710079F508(normal, unk3->_d8, nullptr, material1, material2);
}

Unk_710245a0b8::~Unk_710245a0b8() = default;
Unk_710245a028::~Unk_710245a028() = default;
Unk_710245a000::~Unk_710245a000() = default;
Unk_710245a0e0::~Unk_710245a0e0() = default;

}  // namespace ksys::act
