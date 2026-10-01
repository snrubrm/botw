#include "Game/AI/Action/actionFollowDungeonRotate.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

FollowDungeonRotate::FollowDungeonRotate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FollowDungeonRotate::~FollowDungeonRotate() = default;

bool FollowDungeonRotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FollowDungeonRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody()) {
        body->changeMotionType(ksys::phys::MotionType::Keyframed);
        if (*mIsSetNoHit_s)
            body->setContactLayer(ksys::phys::ContactLayer::EntityNoHit);
    }
    if (*mIsChangeableOnEnter_s)
        mFlags.set(Flag::Changeable);
}

void FollowDungeonRotate::leave_() {
    ksys::act::ai::Action::leave_();
}

void FollowDungeonRotate::loadParams_() {
    getStaticParam(&mIsChangeableOnEnter_s, "IsChangeableOnEnter");
    getStaticParam(&mIsSetNoHit_s, "IsSetNoHit");
}

void FollowDungeonRotate::calc_() {
    m32();
}

void FollowDungeonRotate::m32() {
    if (auto* body = mActor->getMainBody()) {
        sead::Matrix34f mtx;
        mActor->getHomeMtx(&mtx);
        body->changePositionAndRotation(mtx);
    }
}

}  // namespace uking::action
