#pragma once

#include <basis/seadTypes.h>

namespace agl::fx {
class RadialBlur;
}

namespace gsys {

class ParticleScene;

// Partial model. ModelSceneFx::calc 0x7100c2edf4 calls it on the scene's manager and then
// runs the blur object itself.
class EffectRadialBlurMgr {
public:
    void setRadialBlur(ParticleScene* scene, agl::fx::RadialBlur& blur);
};

}  // namespace gsys
