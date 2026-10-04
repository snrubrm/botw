#pragma once

#include <controller/seadMaskControllerWrapper.h>

namespace eui {

// The controller wrapper of a screen (Screen::mUIController, 0x218 bytes; constructor 0x7100becd40). Only the
// part that is used so far is declared.
class UIController : public sead::MaskControllerWrapper {
public:
    // The original uses a distinct ControllerWrapperBase RTTI chain; these remain undecompiled.
    bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* type) const override;
    const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const override;
    static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic();
    static bool checkDerivedRuntimeTypeInfoStatic(const sead::RuntimeTypeInfo::Interface* type);
    UIController();
};

static_assert(sizeof(UIController) == 0x218);

}  // namespace eui
