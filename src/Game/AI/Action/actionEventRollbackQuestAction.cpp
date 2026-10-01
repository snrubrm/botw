#include "Game/AI/Action/actionEventRollbackQuestAction.h"
#include "KingSystem/Quest/qstManager.h"

namespace uking::action {

EventRollbackQuestAction::EventRollbackQuestAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventRollbackQuestAction::~EventRollbackQuestAction() = default;

bool EventRollbackQuestAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: x1/x2 argument setup order swapped (scheduling)
bool EventRollbackQuestAction::oneShot_() {
    auto* quest_mgr = ksys::qst::Manager::instance();
    if (!quest_mgr)
        return false;
    if (mStepName_d.isEmpty())
        return false;
    quest_mgr->sub_7100FD7B30(mQuestName_d, mStepName_d, false);
    return true;
}

void EventRollbackQuestAction::loadParams_() {
    getDynamicParam(&mQuestName_d, "QuestName");
    getDynamicParam(&mStepName_d, "StepName");
}

}  // namespace uking::action
