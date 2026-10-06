#include "Game/AI/Action/actionSlideMoveViewTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SlideMoveViewTarget::SlideMoveViewTarget(const InitArg& arg) : MoveBase(arg) {}

SlideMoveViewTarget::~SlideMoveViewTarget() = default;

bool SlideMoveViewTarget::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void SlideMoveViewTarget::sub_710026F368() {
    sead::Vector3f to_target;
    m32(&to_target);
    to_target.y = 0.0f;
    to_target.normalize();

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    front.y = 0.0f;
    front.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
    if (auto* as_list = mActor->getASList())
        as_list->x_6(9, 0, sead::Mathf::rad2deg(angle) * axis.y);
}

void SlideMoveViewTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710026F368();
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    MoveBase::enter_(params);
}

void SlideMoveViewTarget::leave_() {
    MoveBase::leave_();
}

void SlideMoveViewTarget::loadParams_() {
    MoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void SlideMoveViewTarget::calc_() {
    sub_710026F368();
    MoveBase::calc_();
}

// NON_MATCHING: operand order of the last fadd of the squared length (z*z + (x*x + y*y)).
void SlideMoveViewTarget::m35(ksys::phys::CharacterController* controller,
                              const sead::Vector3f& dir) {
    const sead::Vector3f& view_target = sub_71005D9330(mActor);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f new_dir = view_target;
    new_dir = {new_dir.x - pos.x, 0.0f, new_dir.z - pos.z};
    new_dir.normalize();
    MoveBase::m35(controller, new_dir);
}

void SlideMoveViewTarget::m32(sead::Vector3f* dir) {
    dir->setSub(*mTargetPos_d, mActor->getMtx().getTranslation());
    dir->normalize();
}

}  // namespace uking::action
