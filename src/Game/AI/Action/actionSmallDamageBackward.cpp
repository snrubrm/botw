#include "Game/AI/Action/actionSmallDamageBackward.h"

namespace uking::action {

SmallDamageBackward::SmallDamageBackward(const InitArg& arg) : SmallDamageBackwardBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SmallDamageBackward::~SmallDamageBackward() {
    ;
}

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

void SmallDamageBackward::m34() {
    SmallDamageBackwardBase::m34();
    if (*mIsReStartASByDamage_s)
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

}  // namespace uking::action
