#include "Game/AI/Query/queryCheckJustBeforeEventCancel.h"
#include <evfl/Query.h>
#include "KingSystem/Event/evtManager.h"

namespace uking::query {

CheckJustBeforeEventCancel::CheckJustBeforeEventCancel(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckJustBeforeEventCancel::~CheckJustBeforeEventCancel() = default;

int CheckJustBeforeEventCancel::doQuery() {
    return ksys::evt::Manager::instance()->checkJustBeforeEventCancel();
}

void CheckJustBeforeEventCancel::loadParams(const evfl::QueryArg& arg) {}

void CheckJustBeforeEventCancel::loadParams() {}

}  // namespace uking::query
