#include "Game/AI/Action/actionForkStopWithNavCheck.h"
#include "Game/AI/aiUnk_71007377D4.h"

// 0x71005e1484: source namespace unknown; the Actor query returns a float limit.
f32 sub_71005E1484(ksys::act::Actor* actor);

namespace uking::action {

ForkStopWithNavCheck::ForkStopWithNavCheck(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkStopWithNavCheck::~ForkStopWithNavCheck() = default;

bool ForkStopWithNavCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkStopWithNavCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkStopWithNavCheck::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkStopWithNavCheck::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
}

void ForkStopWithNavCheck::calc_() {
    const f32 ratio = *mPosReduceRatio_s;
    const f32 limit = sub_71005E1484(mActor);
    sub_7100738488(mActor, ratio < limit ? ratio : limit, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, *mRotReduceRatio_s);
}

}  // namespace uking::action
