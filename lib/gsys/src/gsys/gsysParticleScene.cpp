#include <gsys/gsysParticleScene.h>
#include <gsys/gsysEffectModelDrawMgr.h>
#include <gsys/gsysEffectRadialBlurMgr.h>
#include <gsys/gsysModelScene.h>

namespace gsys {

// 0x7100c56618
EffectLightMgr::~EffectLightMgr() = default;

// 0x7100c56690
EffectLensFlareMgr::~EffectLensFlareMgr() = default;

// 0x7100c56780
EffectRadialBlurMgr::~EffectRadialBlurMgr() = default;

// 0x7100c565d0
void ParticleScene::fixPlacementData() {
    mScene->mEffectModelDrawMgr->postCalc();
}

}  // namespace gsys
