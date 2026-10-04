#include "KingSystem/Event/evtEventFlowMgr.h"
#include <thread/seadCriticalSection.h>
#include "KingSystem/Event/evtEventResource.h"

namespace ksys::evt {

// 0x7100dbf588
bool EventFlowMgr::areAllEventFlowsReady() const {
    for (s32 i = 0, n = mSlots.size(); i < n; ++i) {
        s32 state = mSlots[i].mState;
        if (state != 3 && state != 0)
            return false;
    }
    return true;
}

// 0x7100dc0024
bool EventFlowMgr::loadEventResourceForAllEventFlows(bool a1) {
    bool ok = true;
    for (s32 i = 0; i < mSlots.size(); ++i) {
        EventFlow& slot = mSlots[i];
        if (slot.mState != 0)
            ok &= slot.loadEventResource(a1);
    }
    return ok;
}

}  // namespace ksys::evt
