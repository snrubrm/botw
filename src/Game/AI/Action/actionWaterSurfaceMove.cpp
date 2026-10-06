#include "Game/AI/Action/actionWaterSurfaceMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

WaterSurfaceMove::WaterSurfaceMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaterSurfaceMove::~WaterSurfaceMove() = default;

bool WaterSurfaceMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterSurfaceMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _30.value = _30.prev_value = *mSpeed_d / 30.0f;
}

void WaterSurfaceMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaterSurfaceMove::loadParams_() {
    getDynamicParam(&mSpeed_d, "Speed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: register allocation / scheduling of the final fmul only (pos in s9/s10/s8 in the original)
void WaterSurfaceMove::calc_() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    _30.updateStats();
    sead::Matrix34f mtx;
    mActor->getHomeMtx(&mtx);
    auto* body = mActor->getMainBody();
    const f32 distance = (*mTargetPos_d - pos).length();
    f32 step = _30.mean;
    const sead::Vector3f* target = mTargetPos_d;
    if (distance <= step) {
        mtx.setTranslation(*target);
        if (body) {
            body->setTransform(mtx, ksys::phys::PropagateToLinkedMotions{true});
            body->setLinearVelocity(sead::Vector3f::zero);
        }
        setFinished();
        return;
    }
    step *= ksys::VFR::instance()->getDeltaFrame();
    sead::Vector3f to_target = *target - pos;
    sead::Vector3f new_pos;
    const f32 length = to_target.length();
    if (length > step) {
        const sead::Vector3f dir = to_target * (1.0f / length);
        new_pos = pos + dir * step;
    } else {
        new_pos = *target;
    }
    mtx.setTranslation(new_pos);
    if (body)
        body->changePositionAndRotation(mtx);
}

}  // namespace uking::action
