#include "Game/AI/Action/actionDieAnm.h"
#include "Game/AI/aiUnk_710072BA90.h"

namespace uking::action {

DieAnm::DieAnm(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

bool DieAnm::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void DieAnm::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    sub_710072BB28(mActor);
}

void DieAnm::leave_() {
    ActionWithPosAngReduce::leave_();
}

void DieAnm::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void DieAnm::calc_() {
    ActionWithPosAngReduce::calc_();
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
