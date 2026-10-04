#include "Game/AI/Action/actionForkCapsuleWindFollow.h"

namespace uking::action {

ForkCapsuleWindFollow::ForkCapsuleWindFollow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkCapsuleWindFollow::~ForkCapsuleWindFollow() {
    _40.destroy(false);
}

bool ForkCapsuleWindFollow::init_(sead::Heap* heap) {
    _40.sub_71010C42B4();
    return true;
}

void ForkCapsuleWindFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkCapsuleWindFollow::leave_() {
    _40.destroy(false);
}

void ForkCapsuleWindFollow::loadParams_() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mLength_s, "Length");
    getStaticParam(&mDir_s, "Dir");
}

void ForkCapsuleWindFollow::calc_() {
    ksys::act::ai::Action::calc_();
}

bool ForkCapsuleWindFollow::hasUpdateForPreDeleteCb() {
    return true;
}

bool ForkCapsuleWindFollow::updateForPreDelete() {
    return _40.sub_71010C4284();
}

}  // namespace uking::action
