#pragma once

#include "gsys/gsysLightRig.h"
#include <environment/aglEnvObj.h>
#include <environment/aglLight.h>

namespace agl::lght {
class LightPrePass;
}

namespace gsys {

// Constructor C567F8: agl::env::PointLight, then the specular size and glare
// parameters; table 24CF198 reuses agl::env::PointLight's RTTI functions and
// appends setToLightPrePass.
class PointLight : public agl::env::PointLight {
public:
    PointLight();
    ~PointLight() override;

    // 0x7100c56af0 (declared only; body U).
    virtual void setToLightPrePass(agl::lght::LightPrePass* light_pre_pass, int index, f32 a,
                                   f32 b) const;

private:
    agl::utl::Parameter<f32> mSpecularSize;
    agl::utl::Parameter<bool> mIsGlare;
    agl::utl::Parameter<int> mGlareShape;
    agl::utl::Parameter<f32> mGlareSize;
    agl::utl::Parameter<f32> mGlareDirPower;
    agl::utl::Parameter<sead::Vector3f> mGlareDir;
    agl::utl::Parameter<f32> mGlareIntensity;
    agl::utl::Parameter<f32> mGlareDepthOfs;
};
static_assert(sizeof(PointLight) == 0x300);

// TODO
class PointLightRig : public LightRig<PointLight> {
public:
    // 0x7100c56b98 (declared only): the factory 0x7100c57eb4 allocates 0x5b0 bytes.
    PointLightRig();
    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const;

private:
    // The rest of the factory's allocation; the members are not modelled.
    u8 _4a0[0x5b0 - 0x4a0];
};

}  // namespace gsys
