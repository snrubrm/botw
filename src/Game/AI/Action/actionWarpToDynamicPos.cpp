#include "Game/AI/Action/actionWarpToDynamicPos.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

WarpToDynamicPos::WarpToDynamicPos(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToDynamicPos::~WarpToDynamicPos() = default;

bool WarpToDynamicPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToDynamicPos::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f forward = *mTargetFoward_d;
    const sead::Vector3f up = sead::Vector3f::ey;
    sead::Vector3f right = up.cross(forward);
    right.y = 0.0f;
    right.normalize();
    sead::Matrix34f mtx;
    mtx.setBase(0, right);
    mtx.setBase(1, up);
    mtx.setBase(2, forward);
    mtx.setTranslation(*mTargetPos_d);
    auto* actor = mActor;
    actor->setMtx(mtx, true, true);
    actor->nullsub_4648();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FDF0(mtx.getBase(2));
    mFlags.set(Flag::Changeable);
    setFinished();
}

void WarpToDynamicPos::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpToDynamicPos::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetFoward_d, "TargetFoward");
}

void WarpToDynamicPos::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
