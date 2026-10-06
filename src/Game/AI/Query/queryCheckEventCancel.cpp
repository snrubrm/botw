#include "Game/AI/Query/queryCheckEventCancel.h"
#include <evfl/Query.h>
#include "KingSystem/Event/evtManager.h"

namespace uking::query {

CheckEventCancel::CheckEventCancel(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckEventCancel::~CheckEventCancel() = default;

int CheckEventCancel::doQuery() {
    return ksys::evt::Manager::instance()->checkEventCancel();
}

void CheckEventCancel::loadParams(const evfl::QueryArg& arg) {}

void CheckEventCancel::loadParams() {}

}  // namespace uking::query
