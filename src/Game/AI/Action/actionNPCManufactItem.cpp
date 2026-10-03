#include "Game/AI/Action/actionNPCManufactItem.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCManufactItem::NPCManufactItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCManufactItem::~NPCManufactItem() = default;

bool NPCManufactItem::oneShot_() {
    const char* name;
    ksys::gdt::getFlag_PlacedItemName(&name);
    const sead::SafeString name_str = name;
    ui::sub_7100A98408(name_str);
    ksys::gdt::resetFlag_PlacedItemName();
    return true;
}

}  // namespace uking::action
