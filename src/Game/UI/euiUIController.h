#pragma once

#include <controller/seadMaskControllerWrapper.h>

namespace eui {

// The controller wrapper of a screen (Screen::mUIController, 0x218 bytes; constructor 0x7100becd40).
class UIController : public sead::MaskControllerWrapper {
public:
    // Spelled out like SEAD_RTTI_OVERRIDE(UIController, sead::MaskControllerWrapper) except that
    // checkDerivedRuntimeTypeInfoStatic (0x7100bece30) is declared only: its inlined parent chain refers to the
    // original's ControllerWrapperBase RTTI object (0x25f95e0), while data_symbols.csv attributes the
    // lib's ControllerWrapperBase symbol to another class (0x25fd488), which makes `datarefs` report a conflict.
    static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {
        static const sead::RuntimeTypeInfo::Derive<sead::MaskControllerWrapper> typeInfo;
        return &typeInfo;
    }
    static bool checkDerivedRuntimeTypeInfoStatic(const sead::RuntimeTypeInfo::Interface* type);

    SEAD_RTTI_CHECKDERIVEDRUNTIMETYPEINFO_OVERRIDE(UIController)

    const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const override {
        return getRuntimeTypeInfoStatic();
    }

    UIController();
};

static_assert(sizeof(UIController) == 0x218);

}  // namespace eui
