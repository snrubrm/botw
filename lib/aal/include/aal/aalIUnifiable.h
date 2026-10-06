#pragma once

#include <container/seadTList.h>

namespace aal {

class Listener;

/// Something whose positions are unified into one speaker balance (see SpeakerBalanceUnifier).
/// It is a sead::TListNode itself (the node's data is the object itself; the node is the base at +8 after the vtable
/// pointer), so it can be put into the list of a SpeakerBalanceUnifier.
class IUnifiable : public sead::TListNode<IUnifiable*> {
public:
    IUnifiable() : TListNode(this) {}
    virtual ~IUnifiable() = default;

    virtual bool calcUnifiablePositions(const Listener& listener, sead::Vector3<f32>* a,
                                        sead::Vector3<f32>* b) {
        return false;
    }
};
static_assert(sizeof(IUnifiable) == 0x28, "aal::IUnifiable size mismatch");

}  // namespace aal
