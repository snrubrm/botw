#include "KingSystem/Event/evtEventFlowMgr.h"
#include "KingSystem/Event/evtEventResource.h"

namespace ksys::evt {

// 0x7100dc1060
void EventFlow::setState4() {
    mState = 4;
    _c = 0;
}

// 0x7100dc106c
void EventFlow::setState3() {
    mState = 3;
    _c = 0;
}

// 0x7100dc1258
bool EventFlow::loadEventResource(bool a1) {
    if (!mResource)
        return true;
    return mResource->load(a1);
}

}  // namespace ksys::evt
