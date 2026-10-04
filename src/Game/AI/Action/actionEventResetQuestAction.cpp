#include "Game/AI/Action/actionEventResetQuestAction.h"
#include "KingSystem/Quest/qstManager.h"

namespace uking::action {

EventResetQuestAction::EventResetQuestAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventResetQuestAction::~EventResetQuestAction() = default;

bool EventResetQuestAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventResetQuestAction::loadParams_() {
    getDynamicParam(&mQuestName_d, "QuestName");
}

bool EventResetQuestAction::oneShot_() {
    if (auto* quest_mgr = ksys::qst::Manager::instance()) {
        quest_mgr->sub_7100FD78B0(mQuestName_d);
        return true;
    }
    return false;
}

}  // namespace uking::action
