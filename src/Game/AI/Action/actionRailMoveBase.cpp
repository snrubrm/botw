#include "Game/AI/Action/actionRailMoveBase.h"

namespace uking::action {

RailMoveBase::RailMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RailMoveBase::~RailMoveBase() = default;

bool RailMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RailMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
    if (!mASName_d.isEmpty())
        playAS(mASName_d.cstr(), *mIsIgnoreSame_d, *mASSlot_d, *mSequenceBank_d, -1.0f);
}

void RailMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void RailMoveBase::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getDynamicParam(&mASSlot_d, "ASSlot");
    getDynamicParam(&mSequenceBank_d, "SequenceBank");
    getDynamicParam(&mIsIgnoreSame_d, "IsIgnoreSame");
    getDynamicParam(&mASName_d, "ASName");
}

void RailMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

void RailMoveBase::m32() {}

}  // namespace uking::action
