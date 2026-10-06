#include "Game/AI/Action/actionListenerFixPositionAction.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

ListenerFixPositionAction::ListenerFixPositionAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ListenerFixPositionAction::~ListenerFixPositionAction() = default;

bool ListenerFixPositionAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ListenerFixPositionAction::loadParams_() {
    getDynamicParam(&mFixType_d, "FixType");
}

}  // namespace uking::action
