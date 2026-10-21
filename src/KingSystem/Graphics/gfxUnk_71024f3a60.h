#pragma once

#include <gsys/gsysLayer.h>
#include <layer/aglDrawMethod.h>
#include <math/seadMatrix.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace ksys::gfx {

// vtable 0x71024f3a60 (hostio::Node vtable at +0x20); constructor 0x7100f0a588. A gsys layer whose
// render steps are ParticleBeforeLayout, Layout, ParticleAfterLayout and Debug; its two draw methods
// (steps 0 and 2) draw the layout particle groups 10 and 11 (0x7100f0a728).
class Unk_71024f3a60 : public gsys::Layer {
    SEAD_RTTI_OVERRIDE(Unk_71024f3a60, gsys::Layer)
public:
    Unk_71024f3a60();
    ~Unk_71024f3a60() override;

    s32 getRenderStepNum() const override { return 4; }
    sead::SafeString getRenderStepName(s32 step) const override;
    // 0x7100f0a7f0 (declaration only): adds the two draw methods and sets up the inverse view
    // matrix from a perspective nn::ui2d::DrawInfo (1280 x 720).
    void doInitialize(sead::Heap* heap) override;

    // 0x7100f0a728 (placeholder name): the draw method callback; render step 0 draws particle group
    // 10 and step 2 group 11.
    void drawParticlesMaybe(const agl::lyr::RenderInfo& info);
    // 0x7100f0a898 (declaration only; placeholder name): draws the layout particles of `group` when
    // the particle manager has any to draw.
    void drawParticleGroupMaybe(s32 group, const agl::lyr::RenderInfo& info);

private:
    agl::lyr::DrawMethod mParticleBeforeLayout;
    agl::lyr::DrawMethod mParticleAfterLayout;
    // Read by the particle draw 0x7100f0a898 as the view matrix of the particle draw info.
    sead::Matrix34f mInvViewMtx;
};

}  // namespace ksys::gfx
