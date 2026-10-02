#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

ActionWithPosAngReduce::ActionWithPosAngReduce(const InitArg& arg) : ActionEx(arg) {}

void ActionWithPosAngReduce::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ActionWithPosAngReduce::leave_() {
    ActionEx::leave_();
}

void ActionWithPosAngReduce::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
}

// NON_MATCHING: regalloc (the original loads the scale constant after the gravity vector)
void ActionWithPosAngReduce::calc_() {
    auto* actor = mActor;
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, actor);
    gravity = gravity * (1.0f / 900.0f);
    sub_7100738488(actor, *mPosReduceRatio_s, gravity);
    sub_7100738AA8(actor, *mAngReduceRatio_s);
}

}  // namespace uking::action
