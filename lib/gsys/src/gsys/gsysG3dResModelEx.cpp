#include <gsys/gsysG3dResModelEx.h>

namespace gsys {

void G3dResModelEx::countUpReferenceCounter() {
    mReferenceCounter.increment();
}

void G3dResModelEx::countDownReferenceCounter() {
    mReferenceCounter.decrement();
}

}  // namespace gsys
