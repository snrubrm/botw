#include "Game/AI/Action/actionOpenGetDemoDialogDressFairy.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {
// 0x7100a9b2f0 (placeholder name; declared only).
void sub_7100A9B2F0(const sead::SafeString& name);
}  // namespace uking::ui

namespace uking::action {

OpenGetDemoDialogDressFairy::OpenGetDemoDialogDressFairy(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

OpenGetDemoDialogDressFairy::~OpenGetDemoDialogDressFairy() = default;

bool OpenGetDemoDialogDressFairy::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenGetDemoDialogDressFairy::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = false;
}

void OpenGetDemoDialogDressFairy::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenGetDemoDialogDressFairy::loadParams_() {}

void OpenGetDemoDialogDressFairy::calc_() {
    if (isFinished() || isFailed())
        return;
    if (ui::UI::instance()) {
        if (_1c) {
            if (ui::UI::instance()->sub_71010A5CAC())
                return;
            setFinished();
        } else {
            if (!ui::PauseMenuDataMgr::instance())
                return;
            auto* item = ui::PauseMenuDataMgr::instance()->getLastAddedItem();
            if (item->isInInventory()) {
                ui::UI::instance()->x(item->getName());
                const char* name;
                ksys::gdt::getFlag_Shop_SelectItemName(&name, false);
                if (name)
                    ui::sub_7100A9B2F0(sead::SafeString(name));
                _1c = true;
                return;
            }
            setFailed();
        }
    } else {
        setFailed();
    }
    mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
