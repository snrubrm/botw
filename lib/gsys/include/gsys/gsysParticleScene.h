#pragma once

#include <basis/seadTypes.h>
#include <cstddef>

namespace gsys {

class EffectRadialBlurMgr;

// Partial model of one particle scene. Only the effect managers that the ModelSceneFx calls
// reach are placed: ModelSceneFx::calc 0x7100c2edf4 passes the pointer at +0x358 as the
// EffectRadialBlurMgr on which setRadialBlur is called with the scene itself. The rest of the
// class (and its size) is not recovered.
class ParticleScene {
private:
    u8 _0[0x358];

public:
    /* 0x358 */ EffectRadialBlurMgr* mEffectRadialBlurMgr;
};

}  // namespace gsys
