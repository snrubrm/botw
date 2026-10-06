#include "aal/aalNamedObj.h"

namespace aal {

// 0x7100b85aa4 / 0x7100b85ac4
NamedObj::~NamedObj() = default;

// 0x7100b85a2c
void NamedObj::setObjName(const sead::SafeString& name) {
    mName = name;
}

}  // namespace aal
