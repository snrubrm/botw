#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <thread/seadAtomic.h>
#include "gsys/gsysModelCubeMapDrawer.h"
#include "gsys/gsysModelSceneComponent.h"

namespace agl::lght {
class LocalLightMapObj;
}

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
    // 0x7100c348c8 / 0x7100c348dc
    agl::env::CubeMapMgr* getCubeMapMgr();
    bool isCubeMapReady() const;
    // 0x7100c309d0
    void setSceneMaterial(class ModelNW* model);
    // 0x7100c324e8
    void pushBack(const sead::Vector3f& position, agl::lght::LocalLightMapObj* obj);

private:
    u8 _250[0x420 - 0x250];
    /// 0x7100c348dc reads the ready pointer at +0xec0 and 0x7100c348c8 returns +0x458.
    ModelCubeMapDrawer* mEnvCubeMap;  // 420
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
    u8 _458[0x660 - 0x458];
    /// 0x7100c324e8: the array index handed out by the atomic counter.
    sead::Atomic<s32> mCount;  // 660
    agl::lght::LocalLightMapObj** mObjects;  // 668
};

}  // namespace gsys
