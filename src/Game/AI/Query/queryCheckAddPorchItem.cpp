#include "Game/AI/Query/queryCheckAddPorchItem.h"
#include <evfl/Query.h>
#include "Game/UI/uiUtils.h"

namespace uking::query {

CheckAddPorchItem::CheckAddPorchItem(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckAddPorchItem::~CheckAddPorchItem() = default;

int CheckAddPorchItem::doQuery() {
    return ui::checkWeaponFreeSlotImpl(mPorchItemName, *mCount);
}

void CheckAddPorchItem::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Count");
    loadString(arg.param_accessor, "PorchItemName");
}

void CheckAddPorchItem::loadParams() {
    getDynamicParam(&mCount, "Count");
    getDynamicParam(&mPorchItemName, "PorchItemName");
}

}  // namespace uking::query
