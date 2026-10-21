#include "gsys/gsysParticleDrawArg.h"
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

}  // namespace gsys
