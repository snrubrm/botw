#pragma once

#include "gsys/gsysLightRig.h"
#include <environment/aglEnvObj.h>
#include <environment/aglLight.h>

namespace gsys {

// TODO: the derived specular size and glare parameters are not modelled. The size comes from the
// rig object's +0x358 member and the 0x370-byte allocation at 0x7100c62bd0.
class SpotLight : public agl::env::SpotLight {
private:
    u8 _270[0x330 - 0x270];
};

// TODO
class SpotLightRig : public LightRig<SpotLight> {
public:
    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const;
};

}  // namespace gsys
