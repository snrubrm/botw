#include "Game/AI/Action/actionOpenDungeonMessage.h"
#include "Game/UI/uiUI.h"

namespace uking::action {

OpenDungeonMessage::OpenDungeonMessage(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenDungeonMessage::~OpenDungeonMessage() = default;

bool OpenDungeonMessage::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenDungeonMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
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
