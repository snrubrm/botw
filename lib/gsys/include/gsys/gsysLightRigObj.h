#pragma once

#include <environment/aglEnvObj.h>

namespace gsys {

class MaskedSpotLight;
class PointLight;
class SpotLight;

// TODO
template <typename T>
class LightRigObj {
public:
    static const agl::env::TypeInfo* sTypeInfo;
    // The type info's first halfword is the type id; the rig getters load it the same way.
    s32 getTypeID() const { return sTypeInfo->id; }
};

extern template class LightRigObj<MaskedSpotLight>;
extern template class LightRigObj<PointLight>;
extern template class LightRigObj<SpotLight>;

}  // namespace gsys
