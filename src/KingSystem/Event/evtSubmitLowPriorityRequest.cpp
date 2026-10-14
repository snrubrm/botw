#include "KingSystem/Event/evtEventResource.h"

namespace ksys::evt {

bool submitLowPriorityRequest(const LowPrioThreadMgr::Request& request) {
    if (auto* mgr = LowPrioThreadMgr::instance())
        return mgr->submitRequest(request);
    return false;
}

}  // namespace ksys::evt
