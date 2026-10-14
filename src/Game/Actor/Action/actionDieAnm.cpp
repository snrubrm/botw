#include "Game/Actor/Action/actionDieAnm.h"
#include "Game/Actor/aiUnk_710072BA90.h"

namespace uking::action {

DieAnm::DieAnm(const InitArg& arg) : StopBase(arg) {}

bool DieAnm::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void DieAnm::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    sub_710072BB28(mActor);
}

void DieAnm::leave_() {
    StopBase::leave_();
}

void DieAnm::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void DieAnm::calc_() {
    StopBase::calc_();
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
