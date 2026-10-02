#include "Game/AI/Action/actionNotStopXLinkWithDemoVisibleOff.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

NotStopXLinkWithDemoVisibleOff::NotStopXLinkWithDemoVisibleOff(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NotStopXLinkWithDemoVisibleOff::~NotStopXLinkWithDemoVisibleOff() = default;

void NotStopXLinkWithDemoVisibleOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NotStopXLinkWithDemoVisibleOff::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115D0AC();
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2b, false);
}

}  // namespace uking::action
