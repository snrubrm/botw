#include "gsys/gsysPointLight.h"
#include "gsys/gsysSpotLight.h"
#include "gsys/gsysMaskedSpotLight.h"

namespace gsys {

PointLight::PointLight()
    : mSpecularSize(0.0f, "SpecularSize", "ハイライトサイズ", this),
      mIsGlare(false, "IsGlare", "グレア有効", this), mGlareShape(0, "GlareShape", "グレア形状", this),
      mGlareSize(10.0f, "GlareSize", "グレアサイズ", this),
      mGlareDirPower(0.0f, "GlareDirPower", "グレア指向性", this),
      mGlareDir(sead::Vector3f::ez, "GlareDir", "グレア指向", this),
      mGlareIntensity(1.0f, "GlareIntensity", "グレア強度", this),
      mGlareDepthOfs(0.0f, "GlareDepthOfs", "グレア深度オフセット", this) {}

PointLight::~PointLight() = default;

// 0x7100c57d4c
s32 PointLightRig::getTypeID() const {
    return sTypeInfo->id;
}

// 0x7100c578c0 / 0x7100c62588 / 0x7100c7c224
template class LightRig<PointLight>;
template class LightRig<SpotLight>;
template class LightRig<MaskedSpotLight>;

}  // namespace gsys
