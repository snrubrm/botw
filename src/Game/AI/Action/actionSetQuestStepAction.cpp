#include "Game/AI/Action/actionSetQuestStepAction.h"
#include "KingSystem/Quest/qstManager.h"

namespace uking::action {

SetQuestStepAction::SetQuestStepAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetQuestStepAction::~SetQuestStepAction() = default;

bool SetQuestStepAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool SetQuestStepAction::oneShot_() {
    if (auto* quest_mgr = ksys::qst::Manager::instance())
        quest_mgr->setQuestStepFromEvent(mQuestName_d, mStepName_d, *mForceRunTelop_d, false);
    return true;
}

void SetQuestStepAction::loadParams_() {
    getDynamicParam(&mForceRunTelop_d, "ForceRunTelop");
    getDynamicParam(&mQuestName_d, "QuestName");
    getDynamicParam(&mStepName_d, "StepName");
}

}  // namespace uking::action
