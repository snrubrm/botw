#include "gsys/gsysLightRigObj.h"
#include "gsys/gsysMaskedSpotLight.h"
#include "gsys/gsysPointLight.h"
#include "gsys/gsysSpotLight.h"

namespace gsys {

// Defined here so its base-object destructor is visible for the rig objects' inline D0.
PointLight::~PointLight() = default;
SpotLight::~SpotLight() = default;

template class LightRigObj<MaskedSpotLight>;
template class LightRigObj<PointLight>;
template class LightRigObj<SpotLight>;

}  // namespace gsys
