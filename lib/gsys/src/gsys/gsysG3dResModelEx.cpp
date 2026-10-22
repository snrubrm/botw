#include <gsys/gsysG3dResModelEx.h>
#include <gsys/gsysModelResource.h>

namespace gsys {

G3dResModelEx::G3dResModelEx() = default;

// 0x7100c6e7e4
int G3dResModelEx::getBufferNum() const {
    return mResource->getBufferNum();
}

void G3dResModelEx::countUpReferenceCounter() {
    mReferenceCounter.increment();
}

void G3dResModelEx::countDownReferenceCounter() {
    mReferenceCounter.decrement();
}

}  // namespace gsys
