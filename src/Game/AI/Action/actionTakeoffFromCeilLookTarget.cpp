#include "Game/AI/Action/actionTakeoffFromCeilLookTarget.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

TakeoffFromCeilLookTarget::TakeoffFromCeilLookTarget(const InitArg& arg)
    : TakeoffFromCeilLook(arg) {}

TakeoffFromCeilLookTarget::~TakeoffFromCeilLookTarget() = default;

bool TakeoffFromCeilLookTarget::init_(sead::Heap* heap) {
    return TakeoffFromCeilLook::init_(heap);
}

void TakeoffFromCeilLookTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    TakeoffFromCeilLook::enter_(params);
}

void TakeoffFromCeilLookTarget::leave_() {
    TakeoffFromCeilLook::leave_();
}

void TakeoffFromCeilLookTarget::loadParams_() {
    TakeoffFromCeilLook::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void TakeoffFromCeilLookTarget::calc_() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir = *mTargetPos_d;
    dir -= pos;
    ksys::util::sub_71011EFA00(&dir, dir, getUpDir(mActor));
    dir.normalize();
    _74.set(dir);
    TakeoffFromCeilLook::calc_();
}

}  // namespace uking::action
