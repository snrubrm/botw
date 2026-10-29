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
    // 0x7100c6181c (declared only): the factory 0x7100c62b98 allocates 0x5f0 bytes.
    SpotLightRig();
    // Declared only: the rig teardown is not modelled.
    ~SpotLightRig();
    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const;

private:
    // The rest of the factory's allocation; the members are not modelled.
    u8 _4a0[0x5f0 - 0x4a0];
};

}  // namespace gsys
