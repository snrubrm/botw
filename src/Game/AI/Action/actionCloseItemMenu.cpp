#include "Game/AI/Action/actionCloseItemMenu.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

CloseItemMenu::CloseItemMenu(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CloseItemMenu::~CloseItemMenu() = default;

bool CloseItemMenu::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool CloseItemMenu::oneShot_() {
    ui::sub_7100A9F038();
    return ksys::act::ai::Action::oneShot_();
}

void CloseItemMenu::loadParams_() {}

}  // namespace uking::action
