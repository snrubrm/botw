#pragma once

#include <environment/aglEnvObj.h>

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
class OfxLensFlareRig {
public:
    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const;
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
class OfxLargeLensFlareRig {
public:
    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const;
};

}  // namespace gsys
