#include "Game/AI/Action/actionEventAutoSaveAtGameClear.h"
#include "Game/gameItemUtils.h"
#include "Game/gamePlayReport.h"
#include "Game/gameSaveSystem.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::action {

EventAutoSaveAtGameClear::EventAutoSaveAtGameClear(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventAutoSaveAtGameClear::~EventAutoSaveAtGameClear() = default;

bool EventAutoSaveAtGameClear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAutoSaveAtGameClear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::gdt::setBoolByKey(true, mGameClearFlag_d, true);
    reportGanonQuestFinished();
    removeFromInventory("Weapon_Bow_071");
    if (ksys::gdt::getFlag_IsTempAddBowPouch(false)) {
        ksys::gdt::setFlag_BowPorchStockNum(ksys::gdt::getFlag_BowPorchStockNum(false) - 1, false);
        ksys::gdt::setFlag_IsTempAddBowPouch(false, false);
    }
    if (auto* save_system = SaveSystem::instance())
        save_system->requestAutoSaveForGameClear(mGameClearFlag_d);
}

void EventAutoSaveAtGameClear::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventAutoSaveAtGameClear::loadParams_() {
    getDynamicParam(&mRestartYDegree_d, "RestartYDegree");
    getDynamicParam(&mGameClearFlag_d, "GameClearFlag");
    getDynamicParam(&mRestartPoint_d, "RestartPoint");
}

void EventAutoSaveAtGameClear::calc_() {
    auto* save_system = SaveSystem::instance();
    if (save_system && save_system->isFinishedSavingMaybe())
        setFinished();
}

}  // namespace uking::action
