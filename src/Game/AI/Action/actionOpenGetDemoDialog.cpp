#include "Game/AI/Action/actionOpenGetDemoDialog.h"
#include <prim/seadSafeString.h>
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiUI.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

OpenGetDemoDialog::OpenGetDemoDialog(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenGetDemoDialog::~OpenGetDemoDialog() = default;

bool OpenGetDemoDialog::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenGetDemoDialog::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = false;
    _49 = false;
}

void OpenGetDemoDialog::leave_() {
    if (ui::UI::instance()->sub_71010A5CAC())
        ui::UI::instance()->sub_71010A6F04();
}

void OpenGetDemoDialog::loadParams_() {
    getDynamicParam(&mIsInvalidOpenPouch_d, "IsInvalidOpenPouch");
    getDynamicParam(&mUseLastTryGetItemName_d, "UseLastTryGetItemName");
    getDynamicParam(&mEnableMultiGet_d, "EnableMultiGet");
    getDynamicParam(&mTargetActorName_d, "TargetActorName");
}

void OpenGetDemoDialog::calc_() {
    if (isFinished() || isFailed())
        return;

    if (_48) {
        if (ui::UI::instance()->sub_71010A5CAC())
            return;
        setFinished();
        mFlags.set(Flag::Changeable);
        return;
    }

    const bool opened = _49;
    const bool open = ui::UI::instance()->sub_71010A5CAC();
    if (opened) {
        _48 = open;
        return;
    }
    if (open) {
        ui::UI::instance()->sub_71010A6F04();
        return;
    }

    if (*mIsInvalidOpenPouch_d)
        ui::sub_7100A9B2AC();

    if (*mUseLastTryGetItemName_d) {
        if (auto* mgr = ui::PauseMenuDataMgr::instance()) {
            const ui::PouchItem* item = mgr->getLastAddedItem();
            if (item->isInInventory()) {
                if (item->getType() == ui::PouchItemType::Food && *mEnableMultiGet_d &&
                    ksys::gdt::getFlag_GiveItemNumber(false) >= 2) {
                    sead::FixedSafeString<64> multi_name;
                    multi_name.format("%s_00", item->getName().cstr());
                    ui::UI::instance()->x(multi_name);
                } else {
                    ui::UI::instance()->x(item->getName());
                }
                _49 = true;
                return;
            }
        }
    }
    ui::UI::instance()->x(mTargetActorName_d);
    _49 = true;
}

}  // namespace uking::action
