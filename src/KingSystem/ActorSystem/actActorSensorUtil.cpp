#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySetParam.h"
#include "KingSystem/Physics/System/physParamSet.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourcePhysics.h"

using ksys::act::Actor;
using ksys::act::ActorAtk;
using ksys::act::Unk_7102459df8;

namespace ksys::act {

AttackSensor2::AttackSensor2(Actor* actor) : PhysicsUserTag(actor) {
    if (actor && actor->getChemicalStuff())
        _18 |= 0x800;
}

// NON_MATCHING: the original decrements this->_20's count directly (it erases through the list,
// not through each node's mList)
AttackSensor2::~AttackSensor2() {
    for (auto it = _20.robustBegin(), end = _20.robustEnd(); it != end; ++it)
        it->erase();
}

}  // namespace ksys::act

const sead::SafeString* sub_71007A24BC() {
    return &ksys::act::getStr_Atk();
}

const sead::SafeString* sub_71007A24D0() {
    return &ksys::act::getStr_Tgt();
}

const sead::SafeString* sub_71007A24E4() {
    return &ksys::act::getStr_Body();
}

const sead::SafeString* sub_71007A24F8() {
    return &ksys::act::getStr_Chemical();
}

const sead::SafeString* sub_71007A250C() {
    return &ksys::act::getStr_EntitySensor();
}

const sead::SafeString* sub_71007A2520() {
    return &ksys::act::getStr_Secure();
}

const sead::SafeString* sub_71007A2534() {
    return &ksys::act::getStr_Lod();
}

const sead::SafeString* sub_71007A2548() {
    return &ksys::act::getStr_GeneralSensor();
}

void sub_71007A439C(Actor* actor, ksys::act::AttackSensor2Listener* listener) {
    if (auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk()))
        atk->sub_710079E344(listener);
}

void sub_71007A4440(Actor* actor, ksys::act::AttackSensor2Listener* listener) {
    if (auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk()))
        atk->sub_710079E3B8(listener);
}

void sub_71007A397C(Actor* actor) {
    auto* set = actor->getRigidBodyByName(ksys::act::getStr_Tgt().cstr());
    if (!set)
        return;
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return;
    for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i) {
        if (auto* body = set->getRigidBodies()[i])
            body->setContactLayer(ksys::phys::ContactLayer::SensorQueryOnly);
    }
}

void sub_71007A2B64(ksys::phys::RigidBody* body, const sead::Matrix34f* mtx) {
    if (!body)
        return;
    if (mtx)
        body->setTransform(*mtx);
    if (!body->isAddedToWorld() || body->isRemovingBodyFromWorld())
        body->addToWorld();
    if (auto* sensor = sead::DynamicCast<ksys::act::AttackSensor>(body->getUserTag())) {
        ++sensor->_44;
        sensor->_49 = true;
    }
}

void sub_71007A2EB0(ksys::phys::RigidBody* body, Actor* actor,
                    ksys::phys::SystemGroupHandler* handler) {
    if (!body)
        return;
    auto* sensor = sead::DynamicCast<ksys::act::AttackSensor>(body->getUserTag());
    if (!sensor)
        return;
    if (auto* owner = sensor->getActor(nullptr, actor)) {
        const int set_idx = owner->getPhysics()->sub_7100FBB668(ksys::act::getStr_Atk());
        auto* set = owner->getPhysics()->getRigidBodySet(set_idx);
        const int body_idx = set->findBodyIndexByHavokName(body->getHkBodyName());
        auto& set_param =
            owner->getParam()->getRes().mPhysics->getParamSet().getRigidBodySet(set_idx);
        auto& param = set_param.rigid_bodies[body_idx];
        body->setContactLayerAndGroundHitAndHandler(param.getContactLayer(), param.getGroundHit(),
                                                    handler);
    }
    ++sensor->_44;
    sensor->_49 = true;
}

void sub_71007A2C30(Actor* actor, const sead::SafeString& name, const sead::Matrix34f* mtx) {
    auto* set = actor->getRigidBodyByName(ksys::act::getStr_Atk().cstr());
    if (!set)
        return;
    sub_71007A2B64(set->findBodyByHavokName(name), mtx);
}

void sub_71007A2C9C(Actor* actor) {
    auto* set = actor->getRigidBodyByName(ksys::act::getStr_Atk().cstr());
    if (!set)
        return;
    for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i)
        sub_71007A2B64(set->getRigidBodies()[i], nullptr);
}

void sub_71007A2D34(ksys::phys::RigidBody* body) {
    if (body && (body->isAddedToWorld() || body->isAddingBodyToWorld()))
        body->removeFromWorld();
}

void sub_71007A2D7C(Actor* actor, const sead::SafeString& name) {
    auto* set = actor->getRigidBodyByName(ksys::act::getStr_Atk().cstr());
    if (!set)
        return;
    sub_71007A2D34(set->findBodyByHavokName(name));
}

void sub_71007A2E04(Actor* actor) {
    auto* set = actor->getRigidBodyByName(ksys::act::getStr_Atk().cstr());
    if (!set)
        return;
    for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i)
        sub_71007A2D34(set->getRigidBodies()[i]);
}

void sub_71007A302C(Actor* actor, const sead::SafeString& name,
                    ksys::phys::SystemGroupHandler* handler) {
    auto* physics = actor->getPhysics();
    if (!physics)
        return;
    auto* set = physics->findBodyByName(ksys::act::getStr_Atk().cstr());
    if (!set)
        return;
    auto* body = set->findBodyByHavokName(name);
    if (!body)
        return;
    if (auto* sensor = sead::DynamicCast<ksys::act::AttackSensor>(body->getUserTag())) {
        physics->sub_7100FBAF18(body);
        body->setSystemGroupHandler(handler);
        ++sensor->_44;
        sensor->_49 = true;
    }
}

void sub_71007A3258(ksys::phys::RigidBody* body, ksys::phys::SystemGroupHandler* handler) {
    if (body)
        body->setContactLayerAndHandler(ksys::phys::ContactLayer::SensorNoHit, handler);
}

void sub_71007A32E4(Actor* actor, ksys::phys::SystemGroupHandler* handler) {
    auto* set = actor->getRigidBodyByName(ksys::act::getStr_Atk().cstr());
    if (!set)
        return;
    for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i) {
        if (auto* body = set->getRigidBodies()[i])
            body->setContactLayerAndHandler(ksys::phys::ContactLayer::SensorNoHit, handler);
    }
}

void sub_71007A3270(Actor* actor, const sead::SafeString& name,
                    ksys::phys::SystemGroupHandler* handler) {
    auto* set = actor->getRigidBodyByName(ksys::act::getStr_Atk().cstr());
    if (!set)
        return;
    sub_71007A3258(set->findBodyByHavokName(name), handler);
}

void sub_71007A3470(ksys::phys::RigidBody* body) {
    if (body && (!body->isAddedToWorld() || body->isRemovingBodyFromWorld()))
        body->addToWorld();
}

void sub_71007A34B8(Actor* actor, const sead::SafeString& name) {
    auto* set = actor->getRigidBodyByName(ksys::act::getStr_Tgt().cstr());
    if (!set)
        return;
    sub_71007A3470(set->findBodyByHavokName(name));
}

void sub_71007A3540(Actor* actor) {
    auto* set = actor->getRigidBodyByName(ksys::act::getStr_Tgt().cstr());
    if (!set)
        return;
    for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i)
        sub_71007A3470(set->getRigidBodies()[i]);
}

void sub_71007A35EC(ksys::phys::RigidBody* body) {
    if (body && (body->isAddedToWorld() || body->isAddingBodyToWorld()))
        body->removeFromWorld();
}

void sub_71007A3634(Actor* actor, const sead::SafeString& name) {
    auto* set = actor->getRigidBodyByName(ksys::act::getStr_Tgt().cstr());
    if (!set)
        return;
    sub_71007A35EC(set->findBodyByHavokName(name));
}

void sub_71007A36BC(Actor* actor) {
    auto* set = actor->getRigidBodyByName(ksys::act::getStr_Tgt().cstr());
    if (!set)
        return;
    for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i)
        sub_71007A35EC(set->getRigidBodies()[i]);
}

void sub_71007A3768(Actor* actor, ksys::phys::RigidBody* body) {
    if (auto* physics = actor->getPhysics())
        physics->sub_7100FBAF18(body);
}

void sub_71007A3778(Actor* actor, const sead::SafeString& name) {
    auto* physics = actor->getPhysics();
    if (!physics)
        return;
    auto* set = physics->findBodyByName(ksys::act::getStr_Tgt().cstr());
    if (!set)
        return;
    if (auto* body = set->findBodyByHavokName(name))
        physics->sub_7100FBAF18(body);
}

void sub_71007A3800(Actor* actor) {
    auto* physics = actor->getPhysics();
    if (!physics)
        return;
    auto* set = physics->findBodyByName(ksys::act::getStr_Tgt().cstr());
    if (!set)
        return;
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk || !atk->_70)
        return;
    atk->_70->_38 = false;
    physics->sub_7100FBB18C(set);
}

void sub_71007A3900(ksys::phys::RigidBody* body) {
    if (body)
        body->setContactLayer(ksys::phys::ContactLayer::SensorQueryOnly);
}

void sub_71007A3910(Actor* actor, const sead::SafeString& name) {
    auto* set = actor->getRigidBodyByName(ksys::act::getStr_Tgt().cstr());
    if (!set)
        return;
    sub_71007A3900(set->findBodyByHavokName(name));
}

ActorAtk::Unk_710079e64c::Unk1* sub_71007A255C(Actor* actor, int idx) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return nullptr;
    return atk->sub_710079E2C0(idx);
}

ActorAtk::Struct7::AttackInfo* getAttackInfo(Actor* actor, int idx) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return nullptr;
    return atk->getAttackInfo(idx);
}

bool sub_71007A2604(Actor* actor) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return false;
    return atk->m10();
}

s32 sub_71007A26AC(Actor* actor) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return 0;
    return atk->sub_710079E270();
}

bool sub_71007A274C(Actor* actor) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk || !atk->m10())
        return false;
    const s32 num = atk->sub_710079E270();
    for (int i = 0; i < num; ++i) {
        if (atk->sub_710079E2C0(i)->sub_71007A1F68(0x1f81f))
            return true;
    }
    return false;
}

bool hasAttackInfo(Actor* actor) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return false;
    return atk->hasAttackInfoMaybe();
}

s32 getNumAttackInfoMaybe(Actor* actor) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return 0;
    return atk->getNumAttackInfoMaybe();
}

ksys::act::AttackSensor* getActorAttackSensor(Actor* actor) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return nullptr;
    return atk->_40;
}

ksys::act::AttackSensor2* sub_71007A2844(Actor* actor) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return nullptr;
    return atk->_70;
}

void sub_71007A44E4(Actor* actor, bool on) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return;
    if (!on)
        atk->_78 &= ~1;
    else
        atk->_78 |= 1;
}

void sub_71007A458C(Actor* actor, bool on) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return;
    if (!on)
        atk->_78 &= ~2;
    else
        atk->_78 |= 2;
}

bool sub_71007A4064(s32 type) {
    return type == 2 || type == 3;
}

Unk_7102459df8::Unk_710079d5a0::Unk1* sub_71007A40D0(Actor* actor, int idx) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return nullptr;
    return obj->sub_710079CF98(idx);
}

bool sub_71007A4178(Actor* actor, bool ignore_creator) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return false;
    if (ignore_creator && actor->getCreateArgBaseProcLink().hasProc() &&
        actor->getCreateArgBaseProcLink() == obj->sub_710079CF6C(0)->_18) {
        return false;
    }
    return obj->sub_710079CEE8();
}

s32 sub_71007A425C(Actor* actor) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return 0;
    return obj->sub_710079CF08();
}

bool sub_71007A42FC(Actor* actor) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return false;
    return obj->sub_710079CF20();
}

bool isLandedMaybe(Actor* actor, bool ignore_creator) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return false;
    if (ignore_creator && actor->getCreateArgBaseProcLink().hasProc() &&
        actor->getCreateArgBaseProcLink() == obj->sub_710079CF6C(0)->_18) {
        return false;
    }
    return obj->sub_710079CE78();
}

Unk_7102459df8::Unk_7102459e60::Unk1* sub_71007A471C(Actor* actor, int idx) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return nullptr;
    return obj->sub_710079CF40(idx);
}

s32 sub_71007A47C4(Actor* actor) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return 0;
    return obj->sub_710079CE98();
}

bool isBgGroundHit(Actor* actor, bool ignore_creator) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return false;
    if (ignore_creator && actor->getCreateArgBaseProcLink().hasProc() &&
        actor->getCreateArgBaseProcLink() == obj->sub_710079CF6C(0)->_18) {
        return false;
    }
    return obj->sub_710079CEB0();
}

Unk_7102459df8::Unk_7102459e88::Unk1* sub_71007A4948(Actor* actor, int idx) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return nullptr;
    return obj->sub_710079CF6C(idx);
}

s32 sub_71007A49F0(Actor* actor) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return 0;
    return obj->sub_710079CED0();
}
