#include "Game/AI/Query/queryCheckVacancyItem.h"
#include <evfl/Query.h>
#include "KingSystem/System/UIGlue.h"

namespace uking::query {

CheckVacancyItem::CheckVacancyItem(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckVacancyItem::~CheckVacancyItem() = default;

int CheckVacancyItem::doQuery() {
    return ksys::ui::checkVacancyItem() >= *mCount;
}

void CheckVacancyItem::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Count");
}

void CheckVacancyItem::loadParams() {
    getDynamicParam(&mCount, "Count");
}

}  // namespace uking::query
