#include "KingSystem/Event/evtEventResource.h"

namespace ksys::evt {

void submitLowPriorityRequest(const util::LowPrioThreadMgr::Request& request) {
    if (auto* mgr = util::LowPrioThreadMgr::instance())
        mgr->submitRequest(request);
}

}  // namespace ksys::evt
