#include "Game/AI/Action/actionXLinkEventEnable.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

XLinkEventEnable::XLinkEventEnable(const InitArg& arg) : ksys::act::ai::Action(arg) {}

XLinkEventEnable::~XLinkEventEnable() = default;

bool XLinkEventEnable::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void XLinkEventEnable::loadParams_() {
    getDynamicParam(&mIsEnable_d, "IsEnable");
}

bool XLinkEventEnable::oneShot_() {
    xlinkEventOn(mActor, 0x19, *mIsEnable_d, false);
    return true;
}

}  // namespace uking::action
