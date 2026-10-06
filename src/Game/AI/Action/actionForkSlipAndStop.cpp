#include "Game/AI/Action/actionForkSlipAndStop.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

// Declaration only (0x71005e1484); the same declaration is in actionForkStopWithNavCheck.cpp.
f32 sub_71005E1484(ksys::act::Actor* actor);

namespace uking::action {

ForkSlipAndStop::ForkSlipAndStop(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSlipAndStop::~ForkSlipAndStop() = default;

bool ForkSlipAndStop::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSlipAndStop::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkSlipAndStop::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSlipAndStop::loadParams_() {
    getStaticParam(&mPosReduceRatioForSlip_s, "PosReduceRatioForSlip");
    getStaticParam(&mAngReduceRatioForSlip_s, "AngReduceRatioForSlip");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
    getStaticParam(&mUseLineCheck_s, "UseLineCheck");
}

void ForkSlipAndStop::calc_() {
    if (sub_71005DD798(mActor, 47, nullptr, 0, 0)) {
        f32 pos_ratio = *mPosReduceRatioForSlip_s;
        if (*mUseLineCheck_s) {
            pos_ratio = sead::Mathf::clampMax(sub_71005E1484(mActor), pos_ratio);
        }
        sub_7100738488(mActor, pos_ratio, -sead::Vector3f::ey);
        sub_7100738AA8(mActor, *mAngReduceRatioForSlip_s);
    } else {
        f32 pos_ratio = *mPosReduceRatio_s;
        if (*mUseLineCheck_s) {
            pos_ratio = sead::Mathf::clampMax(sub_71005E1484(mActor), pos_ratio);
        }
        sub_7100738488(mActor, pos_ratio, -sead::Vector3f::ey);
        sub_7100738AA8(mActor, *mAngReduceRatio_s);
    }
}

}  // namespace uking::action
