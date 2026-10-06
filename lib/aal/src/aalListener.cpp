#include "aal/aalListener.h"

namespace aal {

// 0x7100b84474 (D1) / 0x7100b84494 (D0)
Listener::~Listener() = default;

// 0x7100b84930
void Listener::setObjName(const sead::SafeString& name) {
    mFixedName.copy(name);
    mName = mFixedName;
}

}  // namespace aal
