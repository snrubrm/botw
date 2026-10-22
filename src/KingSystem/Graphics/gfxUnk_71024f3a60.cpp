#include "KingSystem/Graphics/gfxUnk_71024f3a60.h"
#include "Game/UI/euiTypes.h"
#include <layer/aglRenderInfo.h>
#include <math/seadMatrixCalcCommon.h>
#include <nn/ui2d/DrawInfo.h>
#include <nn/ui2d/Types.h>

namespace ksys::gfx {

// The render step names (pointer table 0x71024f3b48).
static const char* const sRenderStepName[4] = {
    "ParticleBeforeLayout",
    "Layout",
    "ParticleAfterLayout",
    "Debug",
};

Unk_71024f3a60::~Unk_71024f3a60() = default;

sead::SafeString Unk_71024f3a60::getRenderStepName(s32 step) const {
    return sRenderStepName[step];
}

// 0x7100f0a7f0: adds the two particle draw methods and inverts the view matrix of a 1280 x 720
// perspective nn::ui2d::DrawInfo into mInvViewMtx.
// NON_MATCHING: stack-slot packing only: the original puts the DrawInfo at sp and the Size at
// sp+0x108; ours starts the DrawInfo at sp+8. Calls, frame size and saved registers match.
void Unk_71024f3a60::doInitialize(sead::Heap* heap) {
    sub_7100B60B8C(0, &mParticleBeforeLayout);
    sub_7100B60B8C(2, &mParticleAfterLayout);

    nn::ui2d::Size size;
    nn::ui2d::DrawInfo info;
    size.width = 1280.0f;
    size.height = 720.0f;
    eui::SetupDrawInfoPerspective(0.6981317f, &info, size);
    sead::Matrix34CalcCommon<float>::inverse(mInvViewMtx, info.mViewMtx);
}

void Unk_71024f3a60::drawParticlesMaybe(const agl::lyr::RenderInfo& info) {
    switch (info.getStepIndexMaybe()) {
    case 0:
        drawParticleGroupMaybe(10, info);
        break;
    case 2:
        drawParticleGroupMaybe(11, info);
        break;
    }
}

}  // namespace ksys::gfx
