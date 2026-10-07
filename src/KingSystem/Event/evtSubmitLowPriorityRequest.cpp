#include "KingSystem/Event/evtEventResource.h"

namespace ksys::evt {

bool submitLowPriorityRequest(const util::LowPrioThreadMgr::Request& request) {
    if (auto* mgr = util::LowPrioThreadMgr::instance())
        return mgr->submitRequest(request);
    return false;
}

}  // namespace ksys::evt
