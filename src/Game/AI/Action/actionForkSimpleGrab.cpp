#include "Game/AI/Action/actionForkSimpleGrab.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkSimpleGrab::ForkSimpleGrab(const InitArg& arg) : ForkSimpleGrabBase(arg) {}

ForkSimpleGrab::~ForkSimpleGrab() = default;

bool ForkSimpleGrab::init_(sead::Heap* heap) {
    return ForkSimpleGrabBase::init_(heap);
}

void ForkSimpleGrab::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkSimpleGrabBase::enter_(params);
}

void ForkSimpleGrab::leave_() {
    ForkSimpleGrabBase::leave_();
}

void ForkSimpleGrab::loadParams_() {
    ForkSimpleGrabBase::loadParams_();
    getStaticParam(&mCheckRadius_s, "CheckRadius");
}

void ForkSimpleGrab::calc_() {
    ForkSimpleGrabBase::calc_();
}

int ForkSimpleGrab::m32() {
    auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
    if (!child)
        return 0;
    if (sub_7100738FA8(mActor, child))
        return 1;
    const sead::Vector3f diff = mActor->getMtx().getTranslation() - child->getMtx().getTranslation();
    return diff.length() <= *mCheckRadius_s;
}

}  // namespace uking::action
