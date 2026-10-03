#include "Game/AI/Action/actionOpenItemMenu.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

OpenItemMenu::OpenItemMenu(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenItemMenu::~OpenItemMenu() = default;

bool OpenItemMenu::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool OpenItemMenu::oneShot_() {
    if (mMenuType_d)
        ui::sub_7100A9EBB8(*mMenuType_d);
    return ksys::act::ai::Action::oneShot_();
}

void OpenItemMenu::loadParams_() {
    getDynamicParam(&mMenuType_d, "MenuType");
}

}  // namespace uking::action
