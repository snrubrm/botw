#pragma once

#include <basis/seadTypes.h>
#include "gsys/gsysModelSceneComponent.h"

namespace gsys {

// The GI component of a ModelScene (ModelScene +0x3a90). Partial: only the feature
// flags read by the is*Enabled getters are modelled, as pointers to the component's
// unmodelled sub-objects.
class ModelSceneGI : public ModelSceneComponent {
public:
    // 0x7100c309f0 / 0x7100c32bf8 / 0x7100c33f3c / 0x7100c33f90
    bool isEnvCubeMapEnabled() const;
    bool isLightPrePassEnabled() const;
    bool isPlanarReflectionEnabled() const;
    bool isSSIIEnabled() const;

private:
    u8 _250[0x420 - 0x250];
    /// 0x7100c348dc reads the ready flag at +0xec0 and 0x7100c348c8 returns +0x458.
    void* mEnvCubeMap;  // 420
    /// 0x7100c33f3c (planar reflection).
    void* mPlanarReflection;  // 428
    /// 0x7100c33f90 (SSII).
    void* mSSII;  // 430
    void* _438;
    /// 0x7100c340b8 (local reflection).
    void* mLocalReflection;  // 440
    void* _448;
    /// 0x7100c32bf8 (light pre-pass).
    void* mLightPrePass;  // 450
};

}  // namespace gsys
