#include "Game/AI/aiUnk_7102451120.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actSandworm.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "Game/AI/aiUnk_71005D6D10.h"

void sub_7100720140(ksys::act::Actor* actor) {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(actor))
        enemy->_e90 = 1;
}

void sub_710072009C(ksys::act::Actor* actor) {
    sub_71005D8DE8(actor, ksys::act::PlayerInfo::instance()->getPlayerLink(), nullptr, nullptr);
}

void sub_71007200B8(ksys::act::Actor* actor) {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(actor))
        enemy->_e90 = 4;
}

void sub_71007201C8(ksys::act::Actor* actor, const sead::SafeString& name) {
    sub_71007A2C30(actor, name, nullptr);
    sub_71007A302C(actor, name, nullptr);
}

void sub_71007201FC(ksys::act::Actor* actor, const sead::SafeString& name) {
    sub_71007A2D7C(actor, name);
    sub_71007A3270(actor, name, nullptr);
}

void sub_710072022C(ksys::act::Actor* actor) {
    sub_71007A2C9C(actor);
    sub_71007A3140(actor, nullptr);
}

void sub_7100720254(ksys::act::Actor* actor) {
    sub_71007A2E04(actor);
    sub_71007A32E4(actor, nullptr);
}

void sub_7100720330(ksys::act::Actor* actor) {
    if (auto* sensor = getActorAttackSensor(actor))
        sensor->_20 &= ~0x18;
}

void sub_71007209E8(ksys::act::Actor* actor, Unk_71012419b4* arg) {
    xlinkSearchAndEmit(actor, "BombEat", 2, arg);
}

void sub_7100720A00(ksys::act::Actor* actor, Unk_71012419b4* arg) {
    xlinkSearchAndEmit(actor, "InsideBomb", 2, arg);
}

void sub_7100720A18(ksys::act::Actor* actor, Unk_71012419b4* arg) {
    xlinkSearchAndEmit(actor, "BombNotEat", 2, arg);
}

s32 sub_7100720354(const sead::SafeString& name) {
    if (name == "All")
        return 0;
    if (name == "Tail")
        return 1;
    return 2;
}

void sub_7100720454(ksys::act::Actor* actor) {
    auto* set = actor->getRigidBodyByName(sub_71007A24E4()->cstr());
    if (!set)
        return;
    for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i) {
        if (auto* body = set->getRigidBodies()[i]) {
            body->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
            body->enableContactLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
            body->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
        }
    }
}

void sub_7100721670(void* unused, ksys::act::Actor* actor, const sead::SafeString& name) {
    auto* set = actor->getRigidBodyByName(sub_71007A24E4()->cstr());
    if (!set)
        return;
    auto* body = set->findBodyByHavokName(name);
    if (!body)
        return;
    if (auto* instances = actor->getPhysics())
        instances->sub_7100FBD94C(body, true);
    body->changeMotionType(ksys::phys::MotionType::Dynamic);
    body->setGravityFactor(0.0f);
    body->enableGroundCollision(false);
    body->setColImpulseScale(0.0f);
    body->setEntityMotionFlag100(true);
    body->setFlag200();
    body->setContactAll();
    body->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
}

void sub_7100720A70(ksys::act::Actor* actor) {
    uking::dmg::DamageInfoMgr::instance()->get450().sub_710065D5D4(actor);
}

void sub_7100720814(ksys::act::Actor* actor, s32 mode) {
    if (auto* sandworm = sead::DynamicCast<uking::act::Sandworm>(actor))
        sandworm->_14c8 = mode;
    switch (mode) {
    case 0:
        sub_7100720454(actor);
        break;
    case 1:
        sub_7100720510(actor, "Spine_8,Tail_2");
        break;
    }
}

void sub_71007208EC(ksys::act::Actor* actor) {
    if (auto* sandworm = sead::DynamicCast<uking::act::Sandworm>(actor))
        sandworm->_14c8 = 2;
    auto* set = actor->getRigidBodyByName(sub_71007A24E4()->cstr());
    if (!set)
        return;
    for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i) {
        if (auto* body = set->getRigidBodies()[i])
            body->setContactNone();
    }
}

bool Unk_7102451120::invoke(ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
                            const ksys::phys::ContactPointInfo::Event& event) {
    if (event.body->getMotionType() != ksys::phys::MotionType::Dynamic ||
        event.body->hasFlag(ksys::phys::RigidBody::Flag::Fixed) || event.body->getMass() > _8) {
        *disable = ksys::phys::ContactPointInfo::ShouldDisableContact::Yes;
        return false;
    }
    return true;
}

// NON_MATCHING: the last disable block sets the return value after the flag (scheduling)
bool Unk_7102451148::invoke(ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
                            const ksys::phys::ContactPointInfo::Event& event) {
    if (event.body->getMotionType() != ksys::phys::MotionType::Dynamic) {
        switch (event.body->getContactLayer()) {
        case ksys::phys::ContactLayer::EntityGround:
            return true;
        default:
            *disable = ksys::phys::ContactPointInfo::ShouldDisableContact::Yes;
            return false;
        }
    }
    if (event.body->hasFlag(ksys::phys::RigidBody::Flag::Fixed) || event.body->getMass() > _8) {
        *disable = ksys::phys::ContactPointInfo::ShouldDisableContact::Yes;
        return false;
    }
    return true;
}
