#include "aal/aalFxParamSetter.h"

namespace aal {

// 0x71014064fc
FxParamSetter::FxParamSetter() = default;

// 0x7101406514
void FxParamSetter::resetModifiedFlag() {
    mModifiedFlag = 0;
}

// 0x710140651c
void FxParamSetter::reset() {
    mModifiedFlag = 0;
    resetImpl_();
}

// 0x710140652c
bool FxParamSetter::isOnModifiedFlagBit(int bit) const {
    return (1 << bit) & mModifiedFlag;
}

// 0x7101406544
void FxParamSetter::setModifiedFlagBit_(int bit) {
    mModifiedFlag |= 1 << bit;
}

}  // namespace aal
