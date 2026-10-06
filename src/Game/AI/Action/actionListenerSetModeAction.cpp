#include "Game/AI/Action/actionListenerSetModeAction.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

ListenerSetModeAction::ListenerSetModeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ListenerSetModeAction::~ListenerSetModeAction() = default;

bool ListenerSetModeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ListenerSetModeAction::loadParams_() {
    getDynamicParam(&mMode_d, "Mode");
}

}  // namespace uking::action
