#include "Game/AI/Action/actionMimic.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

Mimic::Mimic(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

Mimic::~Mimic() = default;

void Mimic::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    *mIsStartResetMimicry_a = false;
    _80 = 0;
    playAS(mMimicStartASName_s.cstr(), false, 0, 0, -1.0f);
    mFlags.reset(Flag::Changeable);
}

void Mimic::leave_() {
    if (*mMimicryMaterial_a >= 0)
        sub_71005DD27C(mActor, *mMimicryMaterial_a, 0.0f);
    sub_71005DD34C(mActor, true);
    ActionWithPosAngReduce::leave_();
}

void Mimic::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mMimicTime_s, "MimicTime");
    getStaticParam(&mMimicRate_s, "MimicRate");
    getStaticParam(&mMimicStartASName_s, "MimicStartASName");
    getStaticParam(&mMimicLoopASName_s, "MimicLoopASName");
    getStaticParam(&mMimicEndASName_s, "MimicEndASName");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

void Mimic::calc_() {
    ActionWithPosAngReduce::calc_();
    sub_71001E669C();
}

}  // namespace uking::action
