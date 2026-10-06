#include "Game/AI/Action/actionSetRetryDataAction.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/gameSaveSystem.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtSpecialFlagNames.h"

namespace uking::action {

SetRetryDataAction::SetRetryDataAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetRetryDataAction::~SetRetryDataAction() = default;

bool SetRetryDataAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetRetryDataAction::loadParams_() {}

bool SetRetryDataAction::oneShot_() {
    auto* pause_menu = ui::PauseMenuDataMgr::instance();
    auto* gdt_manager = ksys::gdt::Manager::instance();
    if (pause_menu && gdt_manager) {
        if (pause_menu->cannotGetItem("Weapon_Bow_071", 1)) {
            s32 max = 0;
            sead::SafeString flag_name = ksys::gdt::flagname::BowPorchStockNum();
            if (gdt_manager->getParam().get1().getBuffer1()->getMaxValueForS32(&max, flag_name)) {
                const s32 stock = ksys::gdt::getFlag_BowPorchStockNum(false);
                if (stock < max) {
                    ksys::gdt::setFlag_BowPorchStockNum(stock + 1, false);
                    ksys::gdt::setFlag_IsTempAddBowPouch(true, false);
                }
            }
        }
    }

    auto* save_system = SaveSystem::instance();
    if (save_system && !save_system->setRetryData())
        return false;
    return true;
}

}  // namespace uking::action
