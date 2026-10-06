#include "aal/aalListenerMgr.h"
#include "aal/aalListenerPoser.h"

namespace aal {

// 0x7100b84d84
ListenerMgr::ListenerMgr() = default;

// 0x7100b84dc0 (D1) / 0x7100b84f38 (D0)
ListenerMgr::~ListenerMgr() {
    finalize();
}

// 0x7100b84ffc
void ListenerMgr::initialize(s32 num, sead::Heap* heap) {
    if (mInitialized)
        return;
    mListeners.allocBuffer(num, heap);
    mPosers.initOffset(ListenerPoser::getListNodeOffset());
    mInitialized = true;
}

// 0x7100b84e84
void ListenerMgr::finalize() {
    if (mInitialized) {
        mListeners.freeBuffer();
        mPosers.clear();
        mInitialized = false;
    }
}

// NON_MATCHING: the original keeps the null test of the found listener when the names are the same string
// 0x7100b850e4
Listener* ListenerMgr::createListener(const sead::SafeString& name) {
    if (!mListeners.isBufferReady())
        return nullptr;

    Listener* existing = nullptr;
    if (!mListeners.isEmpty()) {
        for (Listener& listener : mListeners) {
            if (listener.getObjName().isEqual(name)) {
                existing = &listener;
                break;
            }
        }
    }
    if (existing)
        return nullptr;

    if (name.isEmpty() || mListeners.isFull())
        return nullptr;

    Listener* listener = mListeners.emplaceBack();
    if (listener)
        listener->setObjName(name);
    return listener;
}

// 0x7100b85298
void ListenerMgr::destroyListener(Listener* listener) {
    if (!mListeners.isBufferReady())
        return;
    if (mListeners.indexOf(listener) >= 0)
        mListeners.erase(listener);
}

// 0x7100b8530c
Listener* ListenerMgr::getListener(s32 index) {
    if (!mListeners.isBufferReady() || index >= mListeners.size())
        return nullptr;
    return mListeners.nth(index);
}

// 0x7100b85354
const Listener* ListenerMgr::getListener(s32 index) const {
    if (!mListeners.isBufferReady() || index >= mListeners.size())
        return nullptr;
    return mListeners.nth(index);
}

// 0x7100b8539c
ListenerPoser* ListenerMgr::findListenerPoser(const sead::SafeString& name) {
    if (mPosers.isEmpty())
        return nullptr;
    for (ListenerPoser& poser : mPosers) {
        if (poser.getObjName().isEqual(name))
            return &poser;
    }
    return nullptr;
}

// 0x7100b854d8
void ListenerMgr::addListenerPoser(ListenerPoser* poser) {
    mPosers.pushBack(poser);
}

// 0x7100b85510
void ListenerMgr::removeListenerPoser(ListenerPoser* poser) {
    if (mPosers.indexOf(poser) >= 0)
        mPosers.erase(poser);
}

}  // namespace aal
