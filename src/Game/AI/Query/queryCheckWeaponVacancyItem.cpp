#include "Game/AI/Query/queryCheckWeaponVacancyItem.h"
#include <evfl/Query.h>

// Source namespace unknown (0x7100ee44e0, in the ksys::act handler TU next to callGetDemoHandler).
bool callCheckWeaponFreeSlotHandler(const sead::SafeString& name, s32 count);

namespace uking::query {

CheckWeaponVacancyItem::CheckWeaponVacancyItem(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckWeaponVacancyItem::~CheckWeaponVacancyItem() = default;

int CheckWeaponVacancyItem::doQuery() {
    return callCheckWeaponFreeSlotHandler("Weapon_Sword_001", *mCount);
}

void CheckWeaponVacancyItem::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Count");
}

void CheckWeaponVacancyItem::loadParams() {
    getDynamicParam(&mCount, "Count");
}

}  // namespace uking::query
