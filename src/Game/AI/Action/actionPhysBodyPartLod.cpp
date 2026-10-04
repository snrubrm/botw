#include "Game/AI/Action/actionPhysBodyPartLod.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

PhysBodyPartLod::PhysBodyPartLod(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PhysBodyPartLod::~PhysBodyPartLod() = default;

bool PhysBodyPartLod::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PhysBodyPartLod::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = false;
    sub_710021A344();
}

void PhysBodyPartLod::leave_() {
    ksys::act::ai::Action::leave_();
}

void PhysBodyPartLod::loadParams_() {
    getStaticParam(&mLodType_s, "LodType");
    getStaticParam(&mRemoveDistance_s, "RemoveDistance");
    getStaticParam(&mRemoveDistanceOffset_s, "RemoveDistanceOffset");
}

// NON_MATCHING: the natural checked body loops and distance branches schedule differently.
void PhysBodyPartLod::sub_710021A344() {
    if (*mLodType_s == 2) {
        if (_38)
            return;
        if (auto* physics = mActor->getPhysics()) {
            const s32 count = physics->getNumRigidBodySets();
            for (s32 i = 0; i < count; ++i) {
                auto* set = physics->getRigidBodySet(i);
                if (set && set->getName().findIndex("BodyParts") != -1)
                    set->addToWorld();
            }
        }
        _38 = true;
    } else if (*mLodType_s == 1) {
        auto* physics = mActor->getPhysics();
        if (!physics)
            return;
        sead::Vector3f position = mActor->getMtx().getTranslation();
        const s32 count = physics->getNumRigidBodySets();
        f32 closest = 100000.0f;
        s32 closest_index = -1;
        for (s32 i = 0; i < count; ++i) {
            auto* set = physics->getRigidBodySet(i);
            if (!set || set->getName().findIndex("BodyParts") == -1)
                continue;
            const s32 body_count = set->getRigidBodies().size();
            for (s32 j = 0; j < body_count; ++j) {
                auto* body = set->getRigidBody(j);
                if (!body)
                    continue;
                body->getPosition(&position);
                f32 distance = 0.0f;
                if (sub_710072B8E4())
                    distance = (position - getPlayerPosition()).length();
                if (distance < closest) {
                    closest = distance;
                    closest_index = i;
                }
            }
        }
        if (!(closest < *mRemoveDistance_s)) {
            closest_index = -1;
        } else if (closest_index >= 0) {
            auto* set = physics->getRigidBodySet(closest_index);
            if (set->hasNoRigidBodyWithFlag8(false))
                set->addToWorld();
        }
        for (s32 i = 0; i < count; ++i) {
            if (i == closest_index)
                continue;
            auto* set = physics->getRigidBodySet(i);
            if (set && set->getName().findIndex("BodyParts") != -1 &&
                !set->hasNoRigidBodyWithFlag8(false))
                set->removeFromWorld();
        }
    } else if (*mLodType_s == 0) {
        auto* set = mActor->getRigidBodyByName("BodyParts_00");
        if (!set)
            return;
        const sead::Vector3f position = mActor->getMtx().getTranslation();
        const bool outside_world = set->hasNoRigidBodyWithFlag8(false);
        f32 distance = 0.0f;
        if (sub_710072B8E4())
            distance = (position - getPlayerPosition()).length();
        if (outside_world) {
            if (distance <= *mRemoveDistance_s - *mRemoveDistanceOffset_s) {
                mActor->getPhysics()->setFlag2();
                set->addToWorld();
            }
        } else if (distance >= *mRemoveDistance_s) {
            set->removeFromWorld();
        }
    }
}

void PhysBodyPartLod::calc_() {
    sub_710021A344();
}

}  // namespace uking::action
