#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>

namespace agl {
class DrawContext;
}

namespace gsys {

// The light-probe component owned by ModelSceneGI at +0x438 (constructor 0x7100c768fc,
// initialize 0x7100c77cd4). Partial: only the enable byte and the empty GPU step are
// modelled.
class LightProbeMgr {
public:
    // 0x7100c76ba8: clears the byte at +0x248.
    void calc();
    // 0x7100c76bb0: empty in this build.
    void calcView(u32 view, const sead::Matrix44f& projection, const sead::Matrix34f& view_mtx);
    // 0x7100c76bb4 / 0x7100c76bb8: the GPU steps are empty in this build.
    void calcGPU();
    void calcGPU(u32 view);
    // 0x7100c76bbc: empty in this build.
    void drawDebug(agl::DrawContext* draw_context, int view) const;
    // Set by ModelSceneGI::initialize 0x7100c3113c and read by calcViewGPU.
    bool isEnabled() const { return mEnabled; }

private:
    u8 _0[0x220];
    u8 mEnabled;  // 220
    u8 _221[0x248 - 0x221];
    u8 _248;
};

}  // namespace gsys
