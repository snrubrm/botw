#include "KingSystem/Event/evtEventFlowMgr.h"
#include "KingSystem/Event/evtEventResource.h"

namespace ksys::evt {

EventFlow* sUnk_7102601530;

// 0x7100dc00e8
EventFlow::EventFlow() : mState(0) {
    mState = 0;
    _c = 0;
    _118 = -1;
    _140 = sead::Vector2f::zero;
    _138 = sead::Vector2f::zero;
    mResource = nullptr;
    mHeap = nullptr;
    _120 = false;
    mRefCount = 0;
}

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

// 0x7100dc01ec
void EventFlow::initAndAllocResource(sead::Heap* heap, const sead::SafeString& event_name,
                                     const sead::SafeString& entry_point,
                                     const al::ByamlIter& info) {
    sUnk_7102601530 = this;
    mEventName.copy(event_name);
    mEntryPointName.copy(entry_point);
    mInfoIter = info;
    mResource = new (heap, 8) EventResource(heap);
    mHeap = heap;
    mResource->_1e0 |= 0x800;
    _120 = false;
    mRefCount = 0;
    mState = 1;
    _c = 0;
    sUnk_7102601530 = nullptr;
}

// 0x7100dc0eec
bool EventFlow::sub_7100DC0EEC() {
    if (mState == 0)
        return true;
    if (mResource) {
        sead::FixedSafeString<128> status;
        mResource->formatInitStatus(&status);
    }
    return false;
}

}  // namespace ksys::evt
