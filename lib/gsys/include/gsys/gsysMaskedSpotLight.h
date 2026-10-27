#pragma once

#include <environment/aglEnvObj.h>
#include "gsys/gsysMaskedLight.h"

namespace gsys {

// Constructor 0x7100c79538 runs the MaskedLight constructor and stores the spot index at +0x2c0.
// Partial: only the index is modelled.
class MaskedSpotLight : public MaskedLight {
public:
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
};

// TODO
class MaskedSpotLightRig {
public:
    static const agl::env::TypeInfo* sTypeInfo;
    s32 getTypeID() const;
};

}  // namespace gsys
