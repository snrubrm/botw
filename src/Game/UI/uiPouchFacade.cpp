#include "Game/UI/uiManager.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiUtils.h"

// UI wrapper functions around uking::ui::PauseMenuDataMgr (the 0x7100a94000 TU).
namespace uking::ui {

// 0x7100a9530c (CSV inventory::getPorchNum)
int getPorchNum(const sead::SafeString& name) {
    if (auto* mgr = PauseMenuDataMgr::instance())
        return mgr->getArrowCount(name);
    return 0;
}

// 0x7100a9532c
int getPorchNumImpl(const sead::SafeString& name) {
    if (auto* mgr = PauseMenuDataMgr::instance())
        return mgr->getRealArrowCount(name);
    return 0;
}

// 0x7100a9b180
bool sub_7100A9B180() {
    if (auto* mgr = PauseMenuDataMgr::instance())
        return mgr->mIsPouchForQuest;
    return false;
}

// 0x7100a99130
void sub_7100A99130() {
    if (auto* mgr = PauseMenuDataMgr::instance())
        mgr->_444fc = 0;
}

// 0x7100a99150
void sub_7100A99150() {
    if (auto* mgr = PauseMenuDataMgr::instance()) {
        mgr->_444fc = 2;
        if (auto* manager = Manager::instance())
            manager->sub_7100A7F890();
    }
}

// 0x7100a99188
void sub_7100A99188() {
    if (auto* mgr = PauseMenuDataMgr::instance()) {
        mgr->_444fc = 1;
        if (auto* manager = Manager::instance())
            manager->sub_7100A7F890();
    }
}

// 0x7100a9e42c
bool checkWeaponFreeSlotImpl(const sead::SafeString& name, s32 count) {
    if (auto* mgr = PauseMenuDataMgr::instance())
        return mgr->checkAddOrRemoveItem(name, count, false);
    return false;
}

// 0x7100a9e488
int checkVacancyItemImpl() {
    if (auto* mgr = PauseMenuDataMgr::instance())
        return mgr->getFreeSlotCount();
    return 0;
}

// 0x7100a9e4a0
int sub_7100A9E4A0(const sead::SafeString& name) {
    if (auto* mgr = PauseMenuDataMgr::instance())
        return mgr->getItemValue(name);
    return 0;
}

// 0x7100a9e4c0
int countCookResultsCheck(const sead::SafeString& name, s32 effect_type) {
    if (auto* mgr = PauseMenuDataMgr::instance())
        return mgr->countCookResults(name, effect_type, true);
    return 0;
}

// 0x7100a9e4ec
int countCookResultsAllOk(const sead::SafeString& name) {
    if (auto* mgr = PauseMenuDataMgr::instance())
        return mgr->countCookResults(name, 0x11, false);
    return 0;
}

// 0x7100a9e514
void pouchDeleteCookResultFromFlow(const sead::SafeString& name, s32 effect_type) {
    if (auto* mgr = PauseMenuDataMgr::instance())
        mgr->removeCookResult(name, effect_type, true);
}

// 0x7100a9e540
void sub_7100A9E540(const sead::SafeString& name) {
    if (auto* mgr = PauseMenuDataMgr::instance())
        mgr->removeCookResult(name, 0x11, false);
}

// 0x7100a9e568
bool inventoryCheckIsOverCategoryLimit() {
    if (auto* mgr = PauseMenuDataMgr::instance())
        return mgr->isOverCategoryLimit(PouchItemType::Food);
    return false;
}

// 0x7100a9e584
void sub_7100A9E584(s32 value) {
    if (auto* mgr = PauseMenuDataMgr::instance())
        mgr->_444fc = value;
    Manager::instance()->sub_7100A7C8D4();
    Manager::instance()->_64c30 |= 1;
}

// 0x7100a9e5f8
void sub_7100A9E5F8(s32 value) {
    if (auto* mgr = PauseMenuDataMgr::instance()) {
        mgr->_444fc = 0;
        mgr->_44500 = value;
    }
    Manager::instance()->sub_7100A7C8D4();
    Manager::instance()->_64c30 |= 1;
}

// 0x7100a9f4c8
void sub_7100A9F4C8() {
    if (auto* mgr = PauseMenuDataMgr::instance())
        mgr->initPouchForQuest();
}

// 0x7100a9f4e0
void sub_7100A9F4E0() {
    if (auto* mgr = PauseMenuDataMgr::instance())
        mgr->restorePouchForQuest();
}

// 0x7100a99278
void recoverMasterSword(bool only_if_broken, bool show_message) {
    if (auto* mgr = PauseMenuDataMgr::instance())
        mgr->restoreMasterSword(only_if_broken);
    if (show_message)
        showInfoOverlayWithString(11, sead::SafeString::cEmptyString);
}

}  // namespace uking::ui
