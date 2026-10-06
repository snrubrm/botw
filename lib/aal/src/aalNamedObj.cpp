#include "aal/aalNamedObj.h"

namespace aal {

// The destructor is inline in the header (its out-of-line copies 0x7100b85aa4 / 0x7100b85ac4 are emitted with the vtable
// next to this function).
// 0x7100b85a2c
void NamedObj::setObjName(const sead::SafeString& name) {
    mName = name;
}

}  // namespace aal
