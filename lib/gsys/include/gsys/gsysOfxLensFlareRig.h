#pragma once

#include <effect/aglFxOfxLensFlare.h>
#include <environment/aglEnvObj.h>
#include "gsys/gsysModelRig.h"
#include "gsys/gsysOfxRig.h"

namespace gsys {

// The vtable (0x71024ce420 / 0x71024ce5a8) holds OfxLensFlare's destructor and effect hooks;
// checkDerivedRuntimeTypeInfo tests only this class and agl::fx::OfxBase, so the RTTI parent is
// OfxBase although the C++ base is OfxLensFlare.
class OfxLensFlareImpl : public agl::fx::OfxLensFlare {
    SEAD_RTTI_OVERRIDE(OfxLensFlareImpl, agl::fx::OfxBase)
public:
    class Preset : public agl::fx::OfxLensFlare::Preset {
        SEAD_RTTI_OVERRIDE(Preset, agl::fx::OfxLensFlare::Preset)
    public:
        static const agl::env::TypeInfo* sTypeInfo;
        s32 getTypeID() const override;
        // 0x7100c4d5fc: the original body returns 5.
        s32 getMaxElementNum() const override;
    };

    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const override;
    // 0x7100c4cde0: the original body returns 5.
    s32 getMaxElementNum() const override;
};

// TODO
class OfxLensFlareRig : public OfxRig<OfxLensFlareImpl> {
    // The factory 0x7100c4d9ec allocates 0x2f0 bytes and calls OfxRig<OfxLensFlareImpl>::OfxRig();
    // the D0 0x7100c4c3b8 then only replaces the first two vtable pointers.
    SEAD_RTTI_OVERRIDE(OfxLensFlareRig, agl::env::EnvObj)
public:
    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const override;

    // 0x7100c4c03c (declared only; body U).
    void updateObj_(OfxRig<OfxLensFlareImpl>::OfxObj* obj, const sead::Matrix34f& matrix,
                    const sead::Vector3f& a, const sead::Vector3f& b) const override;
};
static_assert(sizeof(OfxLensFlareRig) == 0x2f0);

// The vtable (0x71024ce420 / 0x71024ce5a8) holds OfxLensFlare's destructor and effect hooks;
// checkDerivedRuntimeTypeInfo tests only this class and agl::fx::OfxBase, so the RTTI parent is
// OfxBase although the C++ base is OfxLensFlare.
class OfxLargeLensFlareImpl : public agl::fx::OfxLensFlare {
    SEAD_RTTI_OVERRIDE(OfxLargeLensFlareImpl, agl::fx::OfxBase)
public:
    class Preset : public agl::fx::OfxLensFlare::Preset {
        SEAD_RTTI_OVERRIDE(Preset, agl::fx::OfxLensFlare::Preset)
    public:
        static const agl::env::TypeInfo* sTypeInfo;
        s32 getTypeID() const override;
        // 0x7100c4d9b4: the original body returns 20.
        s32 getMaxElementNum() const override;
    };

    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const override;
    // 0x7100c4cf78: the original body returns 20.
    s32 getMaxElementNum() const override;
};

// TODO
class OfxLargeLensFlareRig : public OfxRig<OfxLargeLensFlareImpl> {
    SEAD_RTTI_OVERRIDE(OfxLargeLensFlareRig, agl::env::EnvObj)
public:
    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const override;

    // 0x7100c4c26c (declared only; body U).
    void updateObj_(OfxRig<OfxLargeLensFlareImpl>::OfxObj* obj, const sead::Matrix34f& matrix,
                    const sead::Vector3f& a, const sead::Vector3f& b) const override;
};
static_assert(sizeof(OfxLargeLensFlareRig) == 0x2f0);

}  // namespace gsys
