#pragma once

#include <environment/aglEnvObj.h>
#include "gsys/gsysModelRig.h"

namespace gsys {

// TODO
class OfxLensFlareImpl {
public:
    // TODO
    class Preset {
    public:
        static const agl::env::TypeInfo* sTypeInfo;
        s32 getTypeID() const;
    };

    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const;
};

// TODO
class OfxLensFlareRig : public ModelRig {
    // The D0 0x7100c4c3b8 tail-calls ModelRig::~ModelRig, and checkDerived 0x7100c4c40c falls
    // back to EnvObj's typeinfo, so the class derives from ModelRig but declares EnvObj as its
    // RTTI base.
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
    };

    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const;
};

// TODO
class OfxLargeLensFlareRig : public ModelRig {
    SEAD_RTTI_OVERRIDE(OfxLargeLensFlareRig, agl::env::EnvObj)
public:
    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const override;
};

}  // namespace gsys
