#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <thread/seadAtomic.h>
#include <utility/aglAtomicPtrArray.h>
#include <lighting/aglSSSSS.h>
#include "gsys/gsysLightResMgr.h"
#include "gsys/gsysModelCubeMapDrawer.h"
#include "gsys/gsysModelSceneComponent.h"

namespace agl::pfx {
class GlareFilter;
}

namespace agl::lght {
class LocalLightMapObj;
class LightMapMgr;
class LightPrePass;
class LocalReflection;
class PlanarReflection;
class SSII;
class SSSSS;
}

namespace gsys {

class LightProbeMgr;
class MaskedSpotLightRig;
class Model;
class ModelSceneContext;
class PointLightRig;
class SpotLightRig;

// The GI component of a ModelScene (ModelScene +0x3a90). Partial: only the feature
// flags read by the is*Enabled getters are modelled, as pointers to the component's
// unmodelled sub-objects.
class ModelSceneGI : public ModelSceneComponent {
public:
    // The argument of the light pre-pass calc delegate; the type itself is not modelled.
    struct CalcLightPrePassCallbackArg;
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
    // 0x7100c3250c: copies this frame's objects and updates the per-frame light state.
    void calcWorld();
    // 0x7100c347d0: the GPU steps of SSSSS, SSII and the light probes.
    void calcGPU();
    // 0x7100c32288: draws the SSSSS pass of the current core's context.
    void sssssCallback(const agl::lght::SSSSS::CallbackArg& arg) const;
    // 0x7100c33fb4: copies the camera and projection into the light probes.
    void calcViewLightProbe(const ModelSceneContext& context);
    // 0x7100c32ccc: updates the light map and light pre-pass GPU state.
    void calcGPUDrawBackGround() const;
    // 0x7100c33370: collects the point-light glare filters of the scene.
    void setPointLightGlareFilter(int& index, agl::pfx::GlareFilter* filter) const;
    // 0x7100c32c1c / 0x7100c32c60 / 0x7100c33f60: pass the current view state to the light
    // pre-pass, the light map / SSSSS and SSII.
    void calcViewLightPrePass(const ModelSceneContext& context);
    void calcView(const ModelSceneContext& context);
    void calcViewSSII(const ModelSceneContext& context);
    // 0x7100c34844: the per-view GPU steps of SSSSS, SSII and the light probes.
    void calcViewGPU(const ModelSceneContext& context);
    // 0x7100c33f3c / 0x7100c33f90 / 0x7100c340b8 / 0x7100c347a4
    void releaseLightPrePass(const ModelSceneContext& context) const;
    void releasePlanarReflection(const ModelSceneContext& context) const;
    bool isLocalReflectionEnabled() const;
    void releaseLocalReflection(const ModelSceneContext& context) const;
    // 0x7100c33344
    void releaseSSSSS(const ModelSceneContext& context) const;
    // 0x7100c33a70 / 0x7100c33c04 / 0x7100c33d8c: release a rig through its manager.
    void free(PointLightRig* rig, Model* model, int index);
    void free(SpotLightRig* rig, Model* model, int index);
    void free(MaskedSpotLightRig* rig, Model* model, int index);
    // 0x7100c35194: the component attaches no hostio node of its own.
    void attachHostIO(sead::hostio::Node* node) override {}

private:
    u8 _250[0x420 - 0x250];
    /// 0x7100c348dc reads the ready pointer at +0xec0 and 0x7100c348c8 returns +0x458.
    ModelCubeMapDrawer* mEnvCubeMap;  // 420
    /// 0x7100c33f3c (planar reflection).
    agl::lght::PlanarReflection* mPlanarReflection;  // 428
    /// 0x7100c33f90 (SSII).
    agl::lght::SSII* mSSII;  // 430
    /// 0x7100c34844 (light probes).
    LightProbeMgr* mLightProbeMgr;  // 438
    /// 0x7100c340b8 (local reflection).
    agl::lght::LocalReflection* mLocalReflection;  // 440
    void* _448;
    /// 0x7100c32bf8 (light pre-pass).
    agl::lght::LightPrePass* mLightPrePass;  // 450
    u8 _458[0x458 - 0x458];
    /// 0x7100c32ccc (light map).
    agl::lght::LightMapMgr* mLightMapMgr;  // 458
    /// 0x7100c34844 (SSSSS).
    agl::lght::SSSSS* mSSSSS;  // 460
    u8 _468[0x478 - 0x468];
    /// 0x7100c33a70 / 0x7100c33c04 / 0x7100c33d8c: the rig managers.
    LightResMgr<PointLightRig>* mPointLightResMgr;  // 478
    LightResMgr<SpotLightRig>* mSpotLightResMgr;    // 480
    LightResMgr<MaskedSpotLightRig>* mMaskedSpotLightResMgr;  // 488
    u8 _490[0x660 - 0x490];
    /// 0x7100c324e8: the light map objects registered for the next calcWorld.
    agl::utl::AtomicPtrArray<agl::lght::LocalLightMapObj> mObjects;  // 660
    /// 0x7100c3250c: the objects of the current frame, drawn by drawLightMap.
    agl::utl::AtomicPtrArray<agl::lght::LocalLightMapObj> mFrameObjects;  // 670
    /// 0x7100c33298 / 0x7100c32288: the contexts of the views, sized by the view count in
    /// initialize and indexed by the current core in sssssCallback.
    sead::Buffer<ModelSceneContext*> mContexts;  // 680
    void* _690;
};

}  // namespace gsys
