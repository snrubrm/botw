#include "KingSystem/Event/evtEventFlowMgr.h"
#include <prim/seadScopedLock.h>
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

// 0x7100dbeb4c
EventFlow* EventFlowMgr::loadSimple(const sead::SafeString& event_name,
                                    const sead::SafeString& entry_point) {
    return load(event_name, entry_point, false, false, nullptr);
}

// 0x7100dbf048
void EventFlowMgr::unload(EventFlow* flow) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    flow->unload(true);
}

// 0x7100dbe73c
void EventFlowMgr::calc(bool a1) {
    _b8 = true;
    x_0();
    const s32 n = mSlots.size();
    if (n > 0) {
        if (a1) {
            for (s32 i = 0; i < n; ++i)
                mSlots[i].init(true);
        } else {
            for (s32 i = 0; i < n; ++i) {
                if (i % 5 == mCalcCount % 5)
                    mSlots[i].init(false);
            }
        }
    }
    ++mCalcCount;
    _b8 = false;
}

// 0x7100dbf50c
bool EventFlowMgr::sub_7100DBF50C() {
    for (s32 i = 0; i < mSlots.size(); ++i) {
        EventFlow& slot = mSlots[i];
        if (!slot._120 && !slot.sub_7100DC0EEC())
            return false;
    }
    return true;
}

// 0x7100dbf080
EventFlow* EventFlowMgr::acquireEventFlow(const sead::SafeString& event_name,
                                          const sead::SafeString& entry_point) {
    _b8 = true;
    for (s32 i = 0; i < mSlots.size(); ++i) {
        auto& slot = mSlots[i];
        if (u32(slot.mState - 3) <= 1 && slot.mEventName == event_name &&
            slot.mEntryPointName == entry_point) {
            _b8 = false;
            if (slot.mState == 3) {
                slot.setState4();
                return &slot;
            }
            return nullptr;
        }
    }
    _b8 = false;
    return nullptr;
}

}  // namespace ksys::evt
