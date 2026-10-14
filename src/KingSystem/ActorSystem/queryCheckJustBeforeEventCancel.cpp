#include "KingSystem/ActorSystem/queryCheckJustBeforeEventCancel.h"
#include <evfl/Query.h>
#include "KingSystem/Event/evtManager.h"

namespace ksys::act::ai {

CheckJustBeforeEventCancel::CheckJustBeforeEventCancel(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckJustBeforeEventCancel::~CheckJustBeforeEventCancel() = default;

int CheckJustBeforeEventCancel::doQuery() {
    return ksys::evt::Manager::instance()->checkJustBeforeEventCancel();
}

void CheckJustBeforeEventCancel::loadParams(const evfl::QueryArg& arg) {}

void CheckJustBeforeEventCancel::loadParams() {}

}  // namespace ksys::act::ai
