#pragma once

#include <container/seadTList.h>

namespace aal {

class Listener;

/// Something whose positions are unified into one speaker balance (see SpeakerBalanceUnifier).
/// Keeps itself in a sead::TList through `mListNode` (the node's data is the object itself).
class IUnifiable {
public:
    IUnifiable() : mListNode(this) {}
    virtual ~IUnifiable() = default;

    virtual bool calcUnifiablePositions(const Listener& listener, sead::Vector3<f32>* a,
                                        sead::Vector3<f32>* b) {
        return false;
    }

protected:
    sead::TListNode<IUnifiable*> mListNode;
};
static_assert(sizeof(IUnifiable) == 0x28, "aal::IUnifiable size mismatch");

}  // namespace aal
