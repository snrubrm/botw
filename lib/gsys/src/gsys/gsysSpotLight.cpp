#include "gsys/gsysSpotLight.h"

namespace gsys {

// 0x7100c62a2c
s32 SpotLightRig::getTypeID() const {
    return sTypeInfo->id;
}

}  // namespace gsys

template struct agl::env::EnvObj::TypeToID<gsys::SpotLightRig>;
