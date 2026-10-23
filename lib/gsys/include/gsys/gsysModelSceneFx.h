#pragma once

#include <basis/seadTypes.h>
#include <gsys/gsysModelSceneComponent.h>
#include <utility/aglParameterObj.h>

namespace sead {
class Heap;
namespace hostio {
class Node;
}
}  // namespace sead

namespace agl {
class DrawContext;
namespace env {
class EnvObjMgr;
}
namespace fx {
class Cloud;
class OccludedEffectMgr;
class DecalDrawer;
class DecalSimple;
class DecalTrailMgr;
class DecalAoMgr;
class RadialBlur;
class NormalDrawer;
class VolumeMask;
}  // namespace fx
}  // namespace agl

namespace gsys {

class Model;
class ModelSceneConfig;
class ModelSceneContext;
class ParticleScene;
class RenderBufferContext;
class ModelSceneShadow;

// The ModelScene effect component at ModelScene +0x3478 (0x300 bytes). It is a
// ModelSceneComponent plus an IParameterObj at +0x250; the effect managers it owns start at
// +0x288. The constructor 0x7100c2d630 and initialize 0x7100c2d8b0 allocate them:
// +0x288 OccludedEffectMgr, +0x290 RadialBlur, +0x298 DecalDrawer, +0x2a0 DecalSimple,
// +0x2a8 DecalTrailMgr, +0x2b0 DecalAoMgr, +0x2c0 NormalDrawer, +0x2c8 Cloud,
// +0x2d0 VolumeMask.
class ModelSceneFx : public ModelSceneComponent, public agl::utl::IParameterObj {
public:
    struct CreateArg {
        CreateArg();

        /* 0x0 */ s32 _0;
    };

    ModelSceneFx();
    ~ModelSceneFx() override;

    void initialize(const CreateArg& arg, agl::env::EnvObjMgr* env_obj_mgr, sead::Heap* heap,
                    sead::Heap* heap2);

    void bind(Model* model);
    void unbind(Model* model);
    void calc(ParticleScene* scene);
    void calcDecal();
    void calcView(const ModelSceneContext& context);
    void calcViewOccludedEffect(const ModelSceneContext& context);
    void calcViewGPU(const ModelSceneContext& context);
    bool isCloudEnabled() const;
    bool isDecalEnabled() const;
    bool isVolumeMaskEnabled() const;
    bool isCloudDrawReduceBufffer() const;
    bool isCloudDrawAllocBufffer() const;
    void drawOccludedEffect(agl::DrawContext* context, const ModelSceneContext& scene_context) const;
    void drawDecalBG(agl::DrawContext* context, ModelSceneContext* scene_context) const;
    void drawDebug(agl::DrawContext* context, const ModelSceneContext& scene_context) const override;
    // 0x7100c30184: four-byte body, the component attaches no extra hostio children.
    void attachHostIO(sead::hostio::Node* node) override;
    void releaseWaterNormalModify(int index) const;
    void releaseVolumeMaskTexture(int index) const;

private:
    // Zeroed by the constructor's memset; the effect managers the original allocates sit in
    // here at the offsets listed above.
    /* 0x280 */ u8 _280[0x8];
    /* 0x288 */ agl::fx::OccludedEffectMgr* mOccludedEffect = nullptr;
    /* 0x290 */ agl::fx::RadialBlur* mRadialBlur = nullptr;
    /* 0x298 */ agl::fx::DecalDrawer* mDecalDrawer = nullptr;
    /* 0x2a0 */ agl::fx::DecalSimple* mDecalSimple = nullptr;
    /* 0x2a8 */ agl::fx::DecalTrailMgr* mDecalTrailMgr = nullptr;
    /* 0x2b0 */ agl::fx::DecalAoMgr* mDecalAoMgr = nullptr;
    /* 0x2b8 */ void* _2b8 = nullptr;
    /* 0x2c0 */ agl::fx::NormalDrawer* mNormalDrawer = nullptr;
    /* 0x2c8 */ agl::fx::Cloud* mCloud = nullptr;
    /* 0x2d0 */ agl::fx::VolumeMask* mVolumeMask = nullptr;
    /* 0x2d8 */ f32 _2d8 = 1.0f;
    /* 0x2e0 */ void* _2e0 = nullptr;
    /* 0x2e8 */ void* _2e8 = nullptr;
    /* 0x2f0 */ void* _2f0 = nullptr;
    /* 0x2f8 */ void* _2f8 = nullptr;
};
static_assert(sizeof(ModelSceneFx) == 0x300);

}  // namespace gsys
