#pragma once

#include <environment/aglEnvObj.h>
#include "gsys/gsysModelRig.h"
#include "gsys/gsysOfxRig.h"

namespace gsys {

// TODO
class OfxLensFlareImpl {
public:
    // TODO
    class Preset {
    public:
        static const agl::env::TypeInfo* sTypeInfo;
        s32 getTypeID() const;
        // 0x7100c4d5fc: the original body returns 5.
        s32 getMaxElementNum() const;
    };

    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const;
    // 0x7100c4cde0: the original body returns 5.
    s32 getMaxElementNum() const;
};

// TODO
class OfxLensFlareRig : public OfxRig<OfxLensFlareImpl> {
    // The factory 0x7100c4d9ec allocates 0x2f0 bytes and calls OfxRig<OfxLensFlareImpl>::OfxRig();
    // the D0 0x7100c4c3b8 then only replaces the first two vtable pointers.
    SEAD_RTTI_OVERRIDE(OfxLensFlareRig, agl::env::EnvObj)
public:
    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const override;
};

// TODO
class OfxLargeLensFlareImpl {
public:
    // TODO
    class Preset {
    public:
        static const agl::env::TypeInfo* sTypeInfo;
        s32 getTypeID() const;
        // 0x7100c4d9b4: the original body returns 20.
        s32 getMaxElementNum() const;
    };

    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const;
    // 0x7100c4cf78: the original body returns 20.
    s32 getMaxElementNum() const;
};

// TODO
class OfxLargeLensFlareRig : public OfxRig<OfxLargeLensFlareImpl> {
    SEAD_RTTI_OVERRIDE(OfxLargeLensFlareRig, agl::env::EnvObj)
public:
    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const override;
};

}  // namespace gsys
