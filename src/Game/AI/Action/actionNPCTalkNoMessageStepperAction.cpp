#include "Game/AI/Action/actionNPCTalkNoMessageStepperAction.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

NPCTalkNoMessageStepperAction::NPCTalkNoMessageStepperAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCTalkNoMessageStepperAction::~NPCTalkNoMessageStepperAction() = default;

// NON_MATCHING: the original tests `cmp w21, #1; b.lt` for the missing separator (same shape as BalloonBehavior::m7) and
// schedules `index + 1` before the UI singleton load; ours canonicalises the compare to `<= 0`
void NPCTalkNoMessageStepperAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!ui::UI::instance())
        return;
    const s32 index = mMessageId_d.rfindIndex(":");
    if (index < 1) {
        setFailed();
        return;
    }
    sead::FixedSafeString<64> message_set;
    message_set.copy(mMessageId_d, index);
    ui::UI::instance()->messageDialogViewStyleStuff(
        message_set, sead::SafeString(mMessageId_d.cstr() + (index + 1)), mActor, 0.0f, 1, false,
        false);
    setFinished();
}

void NPCTalkNoMessageStepperAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCTalkNoMessageStepperAction::loadParams_() {
    getDynamicParam(&mMessageId_d, "MessageId");
}

}  // namespace uking::action
