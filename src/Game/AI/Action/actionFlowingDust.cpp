#include "Game/AI/Action/actionFlowingDust.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

FlowingDust::FlowingDust(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FlowingDust::~FlowingDust() = default;

bool FlowingDust::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FlowingDust::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FlowingDust::leave_() {
    ksys::act::ai::Action::leave_();
}

void FlowingDust::loadParams_() {}

void FlowingDust::calc_() {
    if (mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        mActor->emitBasicSigOn();
    else
        mActor->emitBasicSigOff();
}

}  // namespace uking::action
