#pragma once

#include <environment/aglEnvObj.h>

namespace gsys {

// TODO
class SpotLight {};

// TODO
class SpotLightRig {
public:
    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const;
};

}  // namespace gsys
