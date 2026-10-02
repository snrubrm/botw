#include "Game/AI/Action/actionNPCWaitOneTimeAction.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

NPCWaitOneTimeAction::NPCWaitOneTimeAction(const InitArg& arg) : NPCWait(arg) {}

NPCWaitOneTimeAction::~NPCWaitOneTimeAction() = default;

void NPCWaitOneTimeAction::calc_() {
    NPCWait::calc_();
    if (mActor->getASList()->x_4(0, 0))
        setFinished();
}

}  // namespace uking::action
