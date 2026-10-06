#include "aal/aalUnifiablePosition.h"
#include "aal/aalListener.h"

namespace aal {

// 0x7100b94658
bool UnifiablePosition::calcUnifiablePositions(const Listener& listener, sead::Vector3f* a,
                                               sead::Vector3f* b) {
    listener.calcLocalPosition(a, mPosition);
    if (listener.isFlag0xf0())
        listener.calcLocalPositionForAngle(b, mPosition);
    else
        *b = *a;
    return true;
}

}  // namespace aal
