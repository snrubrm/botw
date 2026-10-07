#include "Game/AI/Action/actionOpenDungeonMessage.h"
#include "Game/UI/uiUI.h"

namespace uking::action {

OpenDungeonMessage::OpenDungeonMessage(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenDungeonMessage::~OpenDungeonMessage() = default;

bool OpenDungeonMessage::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenDungeonMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* ui = ui::UI::instance();
    if (!ui) {
        setFailed();
        return;
    }
    const s32 separator = mMessageId_d.rfindIndex(":");
    if (separator >= 1) {
        sead::FixedSafeString<256> message_set;
        message_set.copy(mMessageId_d, separator);
        const sead::SafeString label(mMessageId_d.cstr() + (separator + 1));
        ui->sub_71010A7774(message_set, label, sead::SafeString::cEmptyString,
                         sead::SafeString::cEmptyString, false);
    } else {
        setFailed();
    }
}

void OpenDungeonMessage::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenDungeonMessage::loadParams_() {
    getDynamicParam(&mMessageId_d, "MessageId");
}

void OpenDungeonMessage::calc_() {
    if (isFinishedOrFailed())
        return;
    auto* ui = ui::UI::instance();
    if (!ui) {
        setFailed();
        return;
    }
    if (ui->sub_71010A5DB0())
        setFinished();
}

}  // namespace uking::action
