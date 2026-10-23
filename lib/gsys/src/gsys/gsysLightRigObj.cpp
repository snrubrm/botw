#include "gsys/gsysLightRigObj.h"
#include "gsys/gsysMaskedSpotLight.h"
#include "gsys/gsysPointLight.h"
#include "gsys/gsysSpotLight.h"

namespace gsys {

template class LightRigObj<MaskedSpotLight>;
template class LightRigObj<PointLight>;
template class LightRigObj<SpotLight>;

}  // namespace gsys
