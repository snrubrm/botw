#pragma once

#include <container/seadListImpl.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "aal/aalNamedObj.h"

namespace sead {
class Camera;
}

namespace aal {

/// Places a listener: it calculates the matrices of the listener it is attached to (Listener::setPoser).
/// Every listener poser is registered in the ListenerMgr.
class ListenerPoser : public FixedNamedObj<32>, public sead::hostio::Node {
    SEAD_RTTI_BASE(ListenerPoser)
public:
    static constexpr s32 getListNodeOffset() { return 0x60; }

    explicit ListenerPoser(const sead::SafeString& name);
    ~ListenerPoser() override = default;

    /// Unregisters the poser from the ListenerMgr and deletes it.
    void destroy();

    virtual void reset() { mTarget = nullptr; }
    /// Purpose unknown (stores the 8 bytes it is passed).
    virtual void setTarget(const void* const& target) { mTarget = target; }
    /// Calculates the matrix that transforms from the world to the space of the listener, and the same matrix for the
    /// calculation of the angle. Called by Listener::calc.
    virtual void calcListenerMatrix(sead::Matrix34f* local_matrix, sead::Matrix34f* local_matrix_for_angle) = 0;

protected:
    /// The matrix of the listener from a camera matrix, the position of the listener `position` and an `offset`.
    static void makeListenerMatrix_(sead::Matrix34f* out, const sead::Camera& camera, const sead::Vector3f& position,
                                    const sead::Vector3f& offset);

    const void* mTarget = nullptr;
    /// The node in the list of the posers of the ListenerMgr.
    sead::ListNode mListNode;
};
static_assert(sizeof(ListenerPoser) == 0x70, "aal::ListenerPoser size mismatch");

}  // namespace aal
