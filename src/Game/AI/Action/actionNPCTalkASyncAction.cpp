#include "Game/AI/Action/actionNPCTalkASyncAction.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

NPCTalkASyncAction::NPCTalkASyncAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTalkASyncAction::~NPCTalkASyncAction() = default;

bool NPCTalkASyncAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: scheduling / register allocation of the cNullChar and typeinfo loads (same shape as NPCTalkNoMessageStepperAction::enter_)
bool NPCTalkASyncAction::oneShot_() {
    auto* ui = ui::UI::instance();
    if (!ui)
        return true;
    const s32 index = mMessageId_d.rfindIndex(":");
    if (index < 1)
        return true;
    sead::FixedSafeString<256> message_set;
    message_set.copy(mMessageId_d, index);
    ui->sub_71010A6BEC(mActor, false);
    ui->sub_71010A6454(message_set, mMessageId_d.getPart(index + 1), mActor, f32(*mDispFrame_d),
                       *mIsChecked_d);
    return true;
}

void NPCTalkASyncAction::loadParams_() {
    getDynamicParam(&mDispFrame_d, "DispFrame");
    getDynamicParam(&mIsChecked_d, "IsChecked");
    getDynamicParam(&mMessageId_d, "MessageId");
}

}  // namespace uking::action
