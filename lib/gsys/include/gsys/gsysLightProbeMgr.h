#pragma once

#include <basis/seadTypes.h>

namespace gsys {

// The light-probe component owned by ModelSceneGI at +0x438 (constructor 0x7100c768fc,
// initialize 0x7100c77cd4). Partial: only the enable byte and the empty GPU step are
// modelled.
class LightProbeMgr {
public:
    // 0x7100c76bb4 / 0x7100c76bb8: the GPU steps are empty in this build.
    void calcGPU();
    void calcGPU(u32 view);
    // Set by ModelSceneGI::initialize 0x7100c3113c and read by calcViewGPU.
    bool isEnabled() const { return mEnabled; }

private:
    u8 _0[0x220];
    u8 mEnabled;  // 220
};

}  // namespace gsys
