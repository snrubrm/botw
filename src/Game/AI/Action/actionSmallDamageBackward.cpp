#include "Game/AI/Action/actionSmallDamageBackward.h"

namespace uking::action {

SmallDamageBackward::SmallDamageBackward(const InitArg& arg) : SmallDamageBackwardBase(arg) {}

SmallDamageBackward::~SmallDamageBackward() = default;

bool SmallDamageBackward::init_(sead::Heap* heap) {
    return SmallDamageBackwardBase::init_(heap);
}

void SmallDamageBackward::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamageBackwardBase::enter_(params);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void SmallDamageBackward::leave_() {
    SmallDamageBackwardBase::leave_();
}

void SmallDamageBackward::loadParams_() {
    SmallDamageBackwardBase::loadParams_();
    getStaticParam(&mIsReStartASByDamage_s, "IsReStartASByDamage");
    getStaticParam(&mASName_s, "ASName");
}

void SmallDamageBackward::calc_() {
    SmallDamageBackwardBase::calc_();
}

}  // namespace uking::action
