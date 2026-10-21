#include "gsys/gsysParticleDrawArg.h"
#include <environment/aglFog.h>
#include "gsys/gsysParticleMgr.h"

namespace gsys {

// 0x7100c50b10
void ParticleDrawArg::addParticleGroup(int group) {
    mParticleGroups[mParticleGroupNum] = group;
    mParticleGroupNum++;
    if (u32(group) < 64)
        ParticleMgr::instance()->get_58().setBit(group);
}

// 0x7100c50b60
void ParticleDrawArg::clearParticleGroup() {
    mParticleGroupNum = 0;
}

// 0x7100c50b68
void ParticleDrawArg::setZFog(const agl::env::Fog* fog) {
    mZFog = fog;
    f32 offset = 0.0f;
    f32 scale = 0.0f;
    if (fog) {
        const f32 end = fog->getEnd();
        const f32 start = fog->getStart();
        const f32 range = end - start;
        scale = range != 0.0f ? 1.0f / range : 1.0f;
        offset = -start * scale;
    }
    mZFogScale = scale;
    mZFogOffset = offset;
}

// 0x7100c50bb0
void ParticleDrawArg::setYFog(const agl::env::Fog* fog) {
    mYFog = fog;
    f32 offset = 0.0f;
    f32 scale = 0.0f;
    if (fog) {
        const f32 end = fog->getEnd();
        const f32 start = fog->getStart();
        const f32 range = end - start;
        scale = range != 0.0f ? 1.0f / range : 1.0f;
        offset = -start * scale;
    }
    mYFogScale = scale;
    mYFogOffset = offset;
}

}  // namespace gsys
