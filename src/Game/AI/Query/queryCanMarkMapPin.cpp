#include "Game/AI/Query/queryCanMarkMapPin.h"
#include <evfl/Query.h>
#include "Game/UI/uiUtils.h"

namespace uking::query {

CanMarkMapPin::CanMarkMapPin(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CanMarkMapPin::~CanMarkMapPin() = default;

int CanMarkMapPin::doQuery() {
    return !ui::sub_7100A9A4BC();
}

void CanMarkMapPin::loadParams(const evfl::QueryArg& arg) {}

void CanMarkMapPin::loadParams() {}

}  // namespace uking::query
