#include "aal/aalNamedObj.h"

namespace aal {

// The destructor is inline in the header (its out-of-line copies 0x7100b85aa4 / 0x7100b85ac4 are emitted with the vtable
// next to this function).
// 0x7100b85a2c
void NamedObj::setObjName(const sead::SafeString& name) {
    mName = name;
}

// 0x7100b7feb0 (setObjName), 0x7100b800a4 (D1) / 0x7100b800a8 (D0)
template <s32 N>
void FixedNamedObj<N>::setObjName(const sead::SafeString& name) {
    mFixedName.copy(name);
    mName = mFixedName;
}

template class FixedNamedObj<32>;

}  // namespace aal
