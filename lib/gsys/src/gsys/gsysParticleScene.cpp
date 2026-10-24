#include <gsys/gsysParticleScene.h>
#include <gsys/gsysEffectModelDrawMgr.h>
#include <gsys/gsysModelScene.h>

namespace gsys {

// 0x7100c565d0
void ParticleScene::fixPlacementData() {
    mScene->mEffectModelDrawMgr->postCalc();
}

}  // namespace gsys
