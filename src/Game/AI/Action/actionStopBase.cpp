#include "Game/AI/Action/actionStopBase.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

StopBase::StopBase(const InitArg& arg) : ActionEx(arg) {}

void StopBase::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void StopBase::leave_() {
    ActionEx::leave_();
}

void StopBase::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
}

void StopBase::calc_() {
    auto* actor = mActor;
    const sead::Vector3f gravity = getGravity(actor) * (1.0f / 900.0f);
    sub_7100738488(actor, *mPosReduceRatio_s, gravity);
    sub_7100738AA8(actor, *mAngReduceRatio_s);
}

}  // namespace uking::action
