#include "aal/aalNamedObj.h"

namespace aal {

// The destructor is inline in the header (its out-of-line copies 0x7100b85aa4 / 0x7100b85ac4 are emitted with the vtable
// next to this function).
// 0x7100b85a2c
void NamedObj::setObjName(const sead::SafeString& name) {
    mName = name;
}

// The functions of FixedNamedObj<32> are inline in the header: setObjName 0x7100b7feb0, D1 0x7100b800a4, D0 0x7100b800a8.
template class FixedNamedObj<32>;

}  // namespace aal
