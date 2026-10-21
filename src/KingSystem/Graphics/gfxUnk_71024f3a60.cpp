#include "KingSystem/Graphics/gfxUnk_71024f3a60.h"
#include <layer/aglRenderInfo.h>

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
