#pragma once

#include "gsys/gsysLightRig.h"
#include <environment/aglEnvObj.h>
#include <environment/aglLight.h>

namespace agl::lght {
class LightPrePass;
}

namespace gsys {

// The six glare parameters follow the base at +0x270; the 0x370-byte allocation at 0x7100c62bd0
// also carries the rig object's +0x358 member.
class SpotLight : public agl::env::SpotLight {
public:
    SpotLight();
    ~SpotLight() override;

    // 0x7100c6176c (declared only; body U).
    virtual void setToLightPrePass(agl::lght::LightPrePass* light_pre_pass, int index, f32 a,
                                   f32 b) const;

private:
    // The constructor 0x7100c6152c registers these six glare parameters.
    agl::utl::Parameter<bool> mIsGlare;
    agl::utl::Parameter<int> mGlareShape;
    agl::utl::Parameter<f32> mGlareSize;
    agl::utl::Parameter<f32> mGlareDirPower;
    agl::utl::Parameter<f32> mGlareIntensity;
    agl::utl::Parameter<f32> mGlareDepthOfs;
};
static_assert(sizeof(SpotLight) == 0x330);

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
