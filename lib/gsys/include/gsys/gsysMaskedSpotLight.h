#pragma once

#include "gsys/gsysLightRig.h"
#include <environment/aglEnvObj.h>
#include "gsys/gsysMaskedLight.h"

namespace gsys {

// Constructor 0x7100c79538 runs the MaskedLight constructor and stores the spot index at +0x2c0.
// Partial: only the index is modelled.
class MaskedSpotLight : public MaskedLight {
    SEAD_RTTI_OVERRIDE(MaskedSpotLight, MaskedLight)
public:
    MaskedSpotLight();

    static const agl::env::TypeInfo* sTypeInfo;

    s32 getTypeID() const override;

protected:
    void listenPropertyEventMaskedLight(const sead::hostio::PropertyEvent* event) override;
    void getLightInfo_(agl::lght::LightPrePass* light_pre_pass,
                       agl::lght::LightPrePass::LightInfo* info) const override;
    void setShadowMapImpl_(int index, agl::lght::LightPrePass* light_pre_pass,
                           const agl::TextureSampler* sampler,
                           const sead::Matrix44f& matrix) const override;
    void drawDebugImpl_(agl::DrawContext* context, const sead::Matrix34f& view,
                        const sead::Matrix44f& projection, int view_index) const override;

private:
    /* 0x2c0 */ s32 mIndex = -1;
    // TODO: the derived glare parameters are not modelled. The size comes from the rig object's
    // +0x470 member and the 0x488-byte allocation at 0x7100c7c600.
    u8 _2c8[0x448 - 0x2c8];
};
static_assert(sizeof(MaskedSpotLight) == 0x448);

// TODO
class MaskedSpotLightRig : public LightRig<MaskedSpotLight> {
public:
    // 0x7100c7b6dc (declared only): the factory 0x7100c7c5c8 allocates 0x538 bytes.
    MaskedSpotLightRig();
    // Declared only: the rig teardown is not modelled.
    ~MaskedSpotLightRig();
    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const;

private:
    // The rest of the factory's allocation; the members are not modelled.
    u8 _4a0[0x538 - 0x4a0];
};

}  // namespace gsys
