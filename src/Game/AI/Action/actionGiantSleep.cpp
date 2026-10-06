#include "Game/AI/Action/actionGiantSleep.h"
#include "Game/Actor/actRideable.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

GiantSleep::GiantSleep(const InitArg& arg) : Sleep(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GiantSleep::~GiantSleep() {
    ;
}

bool GiantSleep::init_(sead::Heap* heap) {
    return Sleep::init_(heap);
}

void GiantSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    Sleep::enter_(params);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62BB0();
    if (!mRidableRigidBodyName_s.isEmpty()) {
        auto* actor = mActor;
        auto* physics = actor->getPhysics();
        auto* set = actor->getRigidBodyByName(sub_71007A24E4()->cstr());
        if (physics && set) {
            for (s32 i = 0; i < set->getRigidBodies().size(); ++i) {
                if (auto* body = set->getRigidBody(i)) {
                    body->changeNoCharStandingOnFlag(false);
                    body->setContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
                }
            }
        }
    }
    if (auto* set = mActor->getRigidBodyByName(sub_71007A250C()->cstr()))
        set->removeFromWorld();
}

void GiantSleep::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62BB8();
    if (!mRidableRigidBodyName_s.isEmpty()) {
        auto* actor = mActor;
        auto* physics = actor->getPhysics();
        auto* set = actor->getRigidBodyByName(sub_71007A24E4()->cstr());
        if (physics && set) {
            for (s32 i = 0; i < set->getRigidBodies().size(); ++i) {
                if (auto* body = set->getRigidBody(i)) {
                    physics->sub_7100FBAF18(body);
                    body->changeNoCharStandingOnFlag(true);
                }
            }
        }
    }
    if (auto* set = mActor->getRigidBodyByName(sub_71007A250C()->cstr()))
        set->addToWorld();
    Sleep::leave_();
}

void GiantSleep::loadParams_() {
    Sleep::loadParams_();
    getStaticParam(&mRidableRigidBodyName_s, "RidableRigidBodyName");
    getStaticParam(&mASName_s, "ASName");
}

void GiantSleep::calc_() {
    Sleep::calc_();
}

// NON_MATCHING: the original computes &rideable->_18 after the cstr() call; regalloc
void GiantSleep::m32() {
    if (mASName_s.isEmpty())
        return;
    if (auto* rideable = mActor->m132())
        rideable->_18.sub_7100E786F0(mASName_s.cstr());
    else
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

}  // namespace uking::action
