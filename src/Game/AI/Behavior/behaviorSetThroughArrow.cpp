#include "Game/AI/Behavior/behaviorSetThroughArrow.h"
#include "Game/Actor/actSwarm.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace uking::behavior {

SetThroughArrow::SetThroughArrow(const InitArg& arg) : SetDamageCallback(arg) {}

SetThroughArrow::~SetThroughArrow() = default;

bool SetThroughArrow::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetThroughArrow::m7() {
    SetDamageCallback::m7();
}

void SetThroughArrow::loadParams() {
    SetDamageCallback::loadParams();
}

void SetThroughArrow::m8() {
    SetDamageCallback::m8();
    sub_71007A439C(mActor, &_58);
    if (auto* set = mActor->getRigidBodyByName(ksys::act::getStr_Tgt().cstr())) {
        for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i) {
            if (auto* body = set->getRigidBodies()[i])
                body->setFlag200();
        }
    }
    if (auto* swarm = sead::DynamicCast<uking::act::Swarm>(mActor)) {
        for (int i = 0; i < swarm->_15f8.size(); ++i) {
            if (auto* body = swarm->_15f8[i]._20)
                body->setFlag200();
        }
    }
}

void SetThroughArrow::m9() {
    if (auto* set = mActor->getRigidBodyByName(ksys::act::getStr_Tgt().cstr())) {
        for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i) {
            if (auto* body = set->getRigidBodies()[i])
                body->resetFlag200();
        }
    }
    if (auto* swarm = sead::DynamicCast<uking::act::Swarm>(mActor)) {
        for (int i = 0; i < swarm->_15f8.size(); ++i) {
            if (auto* body = swarm->_15f8[i]._20)
                body->resetFlag200();
        }
    }
    sub_71007A4440(mActor, &_58);
    SetDamageCallback::m9();
}

bool SetThroughArrow::Listener::m0(void* a1, void* a2, void* a3, void* a4, void* a5, void* a6,
                                   const ksys::act::Struct8Base* info, const ksys::act::PhysicsUserTag* tag) {
    return (info->_18 >> 3) & 1;
}

uking::dmg::DamageCallback* SetThroughArrow::m14() {
    return &_30;
}

}  // namespace uking::behavior
