#include "Game/AI/Action/actionSideWalk.h"

namespace uking::action {

SideWalk::SideWalk(const InitArg& arg) : SideWalkBase(arg) {}

SideWalk::~SideWalk() = default;

bool SideWalk::init_(sead::Heap* heap) {
    return SideWalkBase::init_(heap);
}

void SideWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    SideWalkBase::enter_(params);
    if (!mASKeyName_s.isEmpty())
        playAS(mASKeyName_s.cstr(), *mIsIgnoreSameAS_s, 0, 0, -1.0f);
}

void SideWalk::leave_() {
    SideWalkBase::leave_();
}

void SideWalk::loadParams_() {
    SideWalkBase::loadParams_();
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void SideWalk::calc_() {
    SideWalkBase::calc_();
}

}  // namespace uking::action
