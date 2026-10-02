#include "Game/AI/Action/actionForkSeparateThreeASPart.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

ForkSeparateThreeASPart::ForkSeparateThreeASPart(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSeparateThreeASPart::~ForkSeparateThreeASPart() = default;

bool ForkSeparateThreeASPart::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSeparateThreeASPart::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkSeparateThreeASPart::leave_() {
    mActor->getASList()->sub_710115B01C(1, 0, true);
    mActor->getASList()->sub_710115B01C(2, 0, true);
    mActor->getASList()->sub_710115C11C();
}

void ForkSeparateThreeASPart::loadParams_() {
    getStaticParam(&mRootNode_s, "RootNode");
    getStaticParam(&mSlot1StartNode_s, "Slot1StartNode");
    getStaticParam(&mSlot2StartNode_s, "Slot2StartNode");
}

void ForkSeparateThreeASPart::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
