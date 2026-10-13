#include <Havok/Common/Base/hkBase.h>

// NON_MATCHING: existing inline product processes columns in a different order.
void hkMatrix3f::setMul(const hkMatrix3f& a, const hkMatrix3f& b) {
    // Snapshot the left operand before writing an aliased destination.
    const hkMatrix3f lhs = a;
    _setMul(lhs, b);
}

// NON_MATCHING: column product scheduling and register allocation differ.
void hkMatrix3f::mul(const hkMatrix3f& b) {
    hkMatrix3f result;
    result._setMul(*this, b);
    *this = result;
}
