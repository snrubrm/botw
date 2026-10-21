#include <gsys/gsysG3dResModelEx.h>

namespace gsys {

G3dResModelEx::G3dResModelEx() = default;

void G3dResModelEx::countUpReferenceCounter() {
    mReferenceCounter.increment();
}

void G3dResModelEx::countDownReferenceCounter() {
    mReferenceCounter.decrement();
}

}  // namespace gsys
