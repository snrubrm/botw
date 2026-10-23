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
class OfxLensFlareRig;
class OfxLargeLensFlareRig;
class OfxLensFlareImpl;
class OfxLargeLensFlareImpl;

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

    // Manager of the lens-flare rigs of one impl type. The game allocates two: the Lens one at
    // +0x2f0 and the Large one at +0x2f8 (ModelSceneFx::initialize 0x7100c2d8b0). Both are 0x68
    // bytes: a vtable, two PtrArray pairs at +0x8 / +0x18 / +0x28 / +0x38, a Buffer of 0x50-byte
    // hooks at +0x48 and a Buffer of 0x28-byte objects at +0x58 (D2 0x7100c304a4 for the Lens one).
    template <typename Rig, typename Impl>
    class OfxResMgr {
    public:
        // 0x7100c2e350 (Lens) / 0x7100c2e628 (Large): allocates `rig_num` objects of the impl type
        // and `hook_num` rig hooks.
        void initialize(int rig_num, int hook_num, agl::env::EnvObjMgr* env_obj_mgr,
                        agl::fx::OccludedEffectMgr* ofx_mgr, sead::Heap* heap);
        // 0x7100c2ef04 (Lens) / 0x7100c2f0dc (Large)
        void update();
        // 0x7100c301cc (Large) / 0x7100c30338 (Lens): erases every hook of `rig`, `model` and
        // `unit_index` from the active list, detaches it from the model and returns it to the free
        // list.
        void release(Rig* rig, Model* model, int unit_index);
        virtual ~OfxResMgr();
    };

    void initialize(const CreateArg& arg, agl::env::EnvObjMgr* env_obj_mgr, sead::Heap* heap,
                    sead::Heap* heap2);

    void bind(Model* model) override;
    void unbind(Model* model) override;
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
    // 0x7100c2fb7c
    void drawCloud(agl::DrawContext* context, const ModelSceneContext* scene_context) const;
    // 0x7100c30184: four-byte body, the component attaches no extra hostio children.
    void attachHostIO(sead::hostio::Node* node) override;
    void releaseWaterNormalModify(int index) const;
    void releaseVolumeMaskTexture(int index) const;

private:
    // Zeroed by the constructor's memset; the effect managers the original allocates sit in
    // here at the offsets listed above.
    /* 0x280 */ agl::env::EnvObjMgr* mEnvObjMgr = nullptr;
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
    /* 0x2f0 */ OfxResMgr<OfxLensFlareRig, OfxLensFlareImpl>* mOfxLensFlare = nullptr;
    /* 0x2f8 */ OfxResMgr<OfxLargeLensFlareRig, OfxLargeLensFlareImpl>* mOfxLargeLensFlare = nullptr;
};
static_assert(sizeof(ModelSceneFx) == 0x300);

}  // namespace gsys
