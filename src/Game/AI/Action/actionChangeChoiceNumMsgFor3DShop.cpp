#include "Game/AI/Action/actionChangeChoiceNumMsgFor3DShop.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

ChangeChoiceNumMsgFor3DShop::ChangeChoiceNumMsgFor3DShop(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ChangeChoiceNumMsgFor3DShop::~ChangeChoiceNumMsgFor3DShop() = default;

bool ChangeChoiceNumMsgFor3DShop::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeChoiceNumMsgFor3DShop::loadParams_() {}

bool ChangeChoiceNumMsgFor3DShop::oneShot_() {
    const s32 stock = ksys::gdt::getFlag_Shop_PlacedItemStockNum(false);
    if (auto* manager = ui::UI::instance())
        manager->setPlacedItemStockNum(stock > 1, stock);
    return true;
}

}  // namespace uking::action
