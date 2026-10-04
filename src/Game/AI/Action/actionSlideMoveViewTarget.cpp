#include "Game/AI/Action/actionSlideMoveViewTarget.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SlideMoveViewTarget::SlideMoveViewTarget(const InitArg& arg) : MoveBase(arg) {}

SlideMoveViewTarget::~SlideMoveViewTarget() = default;

bool SlideMoveViewTarget::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
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

void SlideMoveViewTarget::m32(sead::Vector3f* dir) {
    dir->setSub(*mTargetPos_d, mActor->getMtx().getTranslation());
    dir->normalize();
}

}  // namespace uking::action
