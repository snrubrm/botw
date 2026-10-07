#pragma once

#include <basis/seadTypes.h>
#include <container/seadObjList.h>
#include <container/seadOffsetList.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include "aal/aalListener.h"

namespace sead {
class Heap;
}

namespace aal {

class ListenerPoser;

/// Owns the listeners and the listener posers.
class ListenerMgr : public sead::hostio::Node {
public:
    ListenerMgr();
    virtual ~ListenerMgr();

    void initialize(s32 num, sead::Heap* heap);
    void finalize();

    /// Returns nullptr if the name is empty or already used by another listener, or if all listeners are used.
    Listener* createListener(const sead::SafeString& name);
    void destroyListener(Listener* listener);
    Listener* getListener(s32 index);
    const Listener* getListener(s32 index) const;

    ListenerPoser* findListenerPoser(const sead::SafeString& name);
    void addListenerPoser(ListenerPoser* poser);
    void removeListenerPoser(ListenerPoser* poser);

    s32 getListenerNum() const { return mListeners.getMaxNum(); }

private:
    friend class SpatialCalculator;
    friend class SoundSource;

    bool mInitialized = false;
    sead::ObjList<Listener> mListeners;
    sead::OffsetList<ListenerPoser> mPosers;
};
static_assert(sizeof(ListenerMgr) == 0x58, "aal::ListenerMgr size mismatch");

}  // namespace aal
