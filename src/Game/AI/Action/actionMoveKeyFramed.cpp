#include "Game/AI/Action/actionMoveKeyFramed.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

MoveKeyFramed::MoveKeyFramed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoveKeyFramed::~MoveKeyFramed() = default;

bool MoveKeyFramed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MoveKeyFramed::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody()) {
        if (body->getMotionType() != ksys::phys::MotionType::Keyframed)
            body->changeMotionType(ksys::phys::MotionType::Keyframed);
    } else {
        setFailed();
    }
    mFlags.set(Flag::Changeable);
}

void MoveKeyFramed::leave_() {
    ksys::act::ai::Action::leave_();
}

void MoveKeyFramed::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mAxisY_d, "AxisY");
    getDynamicParam(&mAxisZ_d, "AxisZ");
}

// NON_MATCHING: instruction scheduling only (the original loads the position pointer before the
// identity stores and interleaves its copy with the cross product)
void MoveKeyFramed::calc_() {
    if (auto* body = mActor->getMainBody()) {
        sead::Vector3f y = *mAxisY_d;
        sead::Vector3f z = *mAxisZ_d;
        y.normalize();
        z.normalize();
        const sead::Vector3f& pos = *mTargetPos_d;
        sead::Matrix34f mtx(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0);
        mtx.setBase(3, pos);
        mtx.setBase(1, y);
        mtx.setBase(2, z);
        sead::Vector3f x;
        x.setCross(y, z);
        mtx.setBase(0, x);
        body->changePositionAndRotation(mtx, sead::Mathf::epsilon());
    }
}

}  // namespace uking::action
